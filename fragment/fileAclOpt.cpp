static DWORD getNewAclSize(PACL dacl,
                           PSID sid,
                           ACL_SIZE_INFORMATION& info,
                           bool needs_allowed,
                           bool needs_denied) {
  // This contains the current buffer size of dacl
  DWORD acl_size = info.AclBytesInUse;

  /*
   * By default, we assume that the ACL as pointed to by the dacl arugment does
   * not contain any access control entries (further known as ACE) associated
   * with sid. If we require an access allowed and/or access denied ACE, we will
   * increment acl_size by the size of the new ACE.
   */

  if (needs_allowed) {
    acl_size +=
        sizeof(ACCESS_ALLOWED_ACE) + ::GetLengthSid(sid) - sizeof(DWORD);
  }

  if (needs_denied) {
    acl_size += sizeof(ACCESS_DENIED_ACE) + ::GetLengthSid(sid) - sizeof(DWORD);
  }

  /*
   * Enumerate the current ACL looking for ACEs associated with sid. Since our
   * assumption is that such a sid does not exist, we need to subtract their
   * size from acl_size if found.
   */
  PACE_HEADER entry = nullptr;
  for (DWORD i = 0; i < info.AceCount; i++) {
    if (!::GetAce(dacl, i, (LPVOID*)&entry)) {
      return 0;
    }

    // We don't care about inherited ACEs
    if ((entry->AceFlags & INHERITED_ACE) == INHERITED_ACE) {
      break;
    }

    if (entry->AceType == ACCESS_ALLOWED_ACE_TYPE &&
        EqualSid(sid, &((ACCESS_ALLOWED_ACE*)entry)->SidStart)) {
      acl_size -=
          sizeof(ACCESS_ALLOWED_ACE) + ::GetLengthSid(sid) - sizeof(DWORD);
    }

    if (entry->AceType == ACCESS_DENIED_ACE_TYPE &&
        EqualSid(sid, &((ACCESS_DENIED_ACE*)entry)->SidStart)) {
      acl_size -=
          sizeof(ACCESS_DENIED_ACE) + ::GetLengthSid(sid) - sizeof(DWORD);
    }
  }

  return acl_size;
}

static Status checkAccessWithSD(PSECURITY_DESCRIPTOR sd, mode_t mode) {
  BOOL status = FALSE;
  DWORD access_rights = 0;
  HANDLE process_token = INVALID_HANDLE_VALUE;
  HANDLE impersonate_token = INVALID_HANDLE_VALUE;

  if ((mode & R_OK) == R_OK) {
    access_rights = GENERIC_READ;
  }

  if ((mode & W_OK) == W_OK) {
    access_rights |= GENERIC_WRITE;
  }

  if ((mode & X_OK) == X_OK) {
    access_rights |= GENERIC_EXECUTE;
  }

  status = OpenProcessToken(
      GetCurrentProcess(),
      TOKEN_IMPERSONATE | TOKEN_QUERY | TOKEN_DUPLICATE | STANDARD_RIGHTS_READ,
      &process_token);
  if (!status) {
    return Status(-1, "OpenProcessToken failed");
  }

  status =
      DuplicateToken(process_token, SecurityImpersonation, &impersonate_token);
  CloseHandle(process_token);

  if (!status) {
    return Status(-1, "DuplicateToken failed");
  }

  GENERIC_MAPPING mapping = {static_cast<ACCESS_MASK>(-1),
                             static_cast<ACCESS_MASK>(-1),
                             static_cast<ACCESS_MASK>(-1),
                             static_cast<ACCESS_MASK>(-1)};
  PRIVILEGE_SET privileges = {0};

  BOOL access_status = FALSE;
  DWORD granted_access = 0;
  DWORD privileges_length = sizeof(privileges);

  mapping.GenericRead = FILE_GENERIC_READ;
  mapping.GenericWrite = FILE_GENERIC_WRITE;
  mapping.GenericExecute = FILE_GENERIC_EXECUTE;
  mapping.GenericAll = FILE_ALL_ACCESS;

  MapGenericMask(&access_rights, &mapping);

  status = AccessCheck(sd,
                       impersonate_token,
                       access_rights,
                       &mapping,
                       &privileges,
                       &privileges_length,
                       &granted_access,
                       &access_status);
  CloseHandle(impersonate_token);

  if (!status) {
    return Status(-1, "AccessCheck failed");
  }

  if (access_status) {
    return Status();
  }

  return Status(1, "Bad mode for file");
}

static Status hasAccess(const fs::path& path, mode_t mode) {
  DWORD result = -1;
  PSECURITY_DESCRIPTOR sd = nullptr;
  SECURITY_INFORMATION security_info = OWNER_SECURITY_INFORMATION |
                                       GROUP_SECURITY_INFORMATION |
                                       DACL_SECURITY_INFORMATION;

  result = GetNamedSecurityInfoW(path.wstring().c_str(),
                                 SE_FILE_OBJECT,
                                 security_info,
                                 nullptr,
                                 nullptr,
                                 nullptr,
                                 nullptr,
                                 &sd);
  if (result != ERROR_SUCCESS) {
    return Status(-1, "GetNamedSecurityInfo failed: " + std::to_string(result));
  }

  auto status = checkAccessWithSD(sd, mode);
  LocalFree(sd);

  return status;
}

static Status hasAccess(HANDLE handle, mode_t mode) {
  BOOL status = FALSE;
  DWORD sd_size = 0;
  SECURITY_INFORMATION security_info = OWNER_SECURITY_INFORMATION |
                                       GROUP_SECURITY_INFORMATION |
                                       DACL_SECURITY_INFORMATION;

  status = GetUserObjectSecurity(handle, &security_info, nullptr, 0, &sd_size);
  if (status || (!status && GetLastError() != ERROR_INSUFFICIENT_BUFFER)) {
    return Status(-1, "GetUserObjectSecurity get SD size error");
  }

  std::vector<char> sd_buffer(sd_size, '\0');
  PSECURITY_DESCRIPTOR sd = (PSECURITY_DESCRIPTOR)sd_buffer.data();
  status = GetUserObjectSecurity(handle, &security_info, sd, sd_size, &sd_size);
  if (!status) {
    return Status(-1, "GetUserObjectSecurity failed");
  }

  return checkAccessWithSD(sd, mode);
}

static AclObject modifyAcl(PACL acl,
                           PSID target,
                           bool allow_read,
                           bool allow_write,
                           bool allow_exec,
                           bool target_is_owner = false) {
  if (acl == nullptr || !IsValidAcl(acl) || target == nullptr ||
      !IsValidSid(target)) {
    return std::move(AclObject());
  }

  /*
   * On POSIX, all users can view the owner, group, world permissions of a file.
   * To mimic this behavior on Windows, we give READ_CONTROL permissions to
   * everyone. READ_CONTROL allows for an user to read the target file's DACL.
   */
  unsigned long allow_mask = READ_CONTROL;
  unsigned long deny_mask = 0;

  ACL_SIZE_INFORMATION info = {0};
  info.AclBytesInUse = sizeof(ACL);

  if (!GetAclInformation(acl, &info, sizeof(info), AclSizeInformation)) {
    return std::move(AclObject());
  }

  if (target_is_owner) {
    /*
     * Owners should always have the ability to delete the target file and
     * modify the target file's DACL
     */
    allow_mask |= DELETE | WRITE_DAC;
  }

  /*
   * We have defined CHMOD_READ, CHMOD_WRITE, and CHMOD_EXECUTE as combinations
   * of Windows access masks in order to simulate the intended effects of the r,
   * w, x permissions of POSIX. In order to correctly simulate the permissions,
   * any permissions set will be explicitly allowed and any permissions that are
   * unset are explicitly denied. This is all done via access allowed and access
   * denied ACEs.
   *
   * We add additional rights for allow cases because we do not want to pollute
   * the CHMOD_* with overlapping rights. For instance, adding SYNCHRONIZE to
   * both CHMOD_READ and CHMOD_EXECUTE will be problematic if execute is denied.
   * SYNCHRONIZE will be added to a deny access control entry which will prevent
   * even a GENERIC_READ from occurring.
   */

  if (allow_read) {
    allow_mask |= CHMOD_READ | FILE_READ_ATTRIBUTES | SYNCHRONIZE;
  } else {
    deny_mask |= CHMOD_READ;
  }

  if (allow_write) {
    allow_mask |= CHMOD_WRITE | DELETE | SYNCHRONIZE;
  } else {
    // Only deny DELETE if the principal is not the owner
    if (!target_is_owner) {
      deny_mask |= DELETE;
    }

    deny_mask |= CHMOD_WRITE;
  }

  if (allow_exec) {
    allow_mask |= CHMOD_EXECUTE | FILE_READ_ATTRIBUTES | SYNCHRONIZE;
  } else {
    deny_mask |= CHMOD_EXECUTE;
  }

  // Only if r and x are denied do we deny FILE_READ_ATTRIBUTES
  if (!allow_read && !allow_exec) {
    deny_mask |= FILE_READ_ATTRIBUTES;
  }

  unsigned long new_acl_size = 0;
  if (allow_read && allow_write && allow_exec) {
    new_acl_size = getNewAclSize(acl, target, info, true, false);
  } else {
    new_acl_size = getNewAclSize(acl, target, info, true, true);
  }

  AclObject new_acl_buffer(new unsigned char[new_acl_size]);
  PACL new_acl = reinterpret_cast<PACL>(new_acl_buffer.get());

  if (!InitializeAcl(new_acl, new_acl_size, ACL_REVISION)) {
    return std::move(AclObject());
  }

  /*
   * Enumerate through the old ACL and copy over all the non-relevant ACEs
   * (read: ACEs that are inherited and not associated with the specified sid).
   * We disregard the ACEs associated with our sid in the old ACL and replace
   * them with updated access masks.
   *
   * The curious bit here is how we order things. In normal Windows ACLs, the
   * ACEs are ordered in a fashion where access denied ACEs have priority to
   * access allowed ACEs. While this is a strong policy, this doesn't fit into
   * our use case and in fact, hurts it. Setting 0600 would prevent even the
   * owner from reading/writing! To counter this, we selectively order the ACEs
   * in our new ACL to fit our needs. This will generate complaints with tools
   * that deal with viewing or modifying the ACL (such as File Explorer).
   */

  unsigned long i = 0;
  LPVOID void_ent = nullptr;
  for (i = 0; i < info.AceCount; i++) {
    if (!GetAce(acl, i, &void_ent)) {
      return std::move(AclObject());
    }

    auto entry = static_cast<PACE_HEADER>(void_ent);
    if ((entry->AceFlags & INHERITED_ACE) == INHERITED_ACE) {
      break;
    }

    auto allowed_ace = reinterpret_cast<ACCESS_ALLOWED_ACE*>(entry);
    auto denied_ace = reinterpret_cast<ACCESS_DENIED_ACE*>(entry);
    if ((entry->AceType == ACCESS_ALLOWED_ACE_TYPE &&
         EqualSid(target, &allowed_ace->SidStart)) ||
        (entry->AceType == ACCESS_DENIED_ACE_TYPE &&
         EqualSid(target, &denied_ace->SidStart))) {
      continue;
    }

    if (!AddAce(new_acl, ACL_REVISION, MAXDWORD, entry, entry->AceSize)) {
      return std::move(AclObject());
    }
  }

  if (deny_mask != 0 &&
      !AddAccessDeniedAce(new_acl, ACL_REVISION, deny_mask, target)) {
    return std::move(AclObject());
  }

  if (allow_mask != 0 &&
      !AddAccessAllowedAce(new_acl, ACL_REVISION, allow_mask, target)) {
    return std::move(AclObject());
  }

  for (; i < info.AceCount; i++) {
    if (!GetAce(acl, i, &void_ent)) {
      return std::move(AclObject());
    }

    auto entry = static_cast<PACE_HEADER>(void_ent);
    if (!AddAce(new_acl, ACL_REVISION, MAXDWORD, void_ent, entry->AceSize)) {
      return std::move(AclObject());
    }
  }

  return std::move(new_acl_buffer);
}

bool PlatformFile::isSpecialFile() const {
  return (GetFileType(handle_) != FILE_TYPE_DISK);
}

static Status isUserCurrentUser(PSID user) {
  if (!IsValidSid(user)) {
    return Status(-1, "Invalid SID");
  }

  HANDLE token = INVALID_HANDLE_VALUE;
  if (!OpenProcessToken(GetCurrentProcess(), TOKEN_READ, &token)) {
    return Status(-1, "OpenProcessToken failed");
  }

  unsigned long size = 0;
  auto ret = GetTokenInformation(token, TokenUser, nullptr, 0, &size);
  if (ret || (!ret && GetLastError() != ERROR_INSUFFICIENT_BUFFER)) {
    CloseHandle(token);

    return Status(
        -1,
        "GetTokenInformation failed (" + std::to_string(GetLastError()) + ")");
  }

  /// Obtain the user SID behind the token handle
  std::vector<char> tuBuff(size, '\0');
  ret = GetTokenInformation(token, TokenUser, tuBuff.data(), size, &size);
  CloseHandle(token);

  if (!ret) {
    return Status(
        -1,
        "GetTokenInformation failed (" + std::to_string(GetLastError()) + ")");
  }

  /// Determine if the current user SID matches that of the specified user
  PTOKEN_USER ptu = reinterpret_cast<PTOKEN_USER>(tuBuff.data());
  if (EqualSid(user, ptu->User.Sid)) {
    return Status();
  }

  return Status(1, "User not current user");
}

Status PlatformFile::isOwnerRoot() const {
  if (!isValid()) {
    return Status(-1, "Invalid file handle value");
  }

  PSID owner = nullptr;
  PSECURITY_DESCRIPTOR sd = nullptr;
  if (GetSecurityInfo(handle_,
                      SE_FILE_OBJECT,
                      OWNER_SECURITY_INFORMATION,
                      &owner,
                      nullptr,
                      nullptr,
                      nullptr,
                      &sd) != ERROR_SUCCESS) {
    return Status(1, "GetSecurityInfo failed");
  }

  SecurityDescriptor sd_wrapper(sd);
  DWORD sid_buff_size = SECURITY_MAX_SID_SIZE;

  std::vector<char> admins_buf(sid_buff_size, '\0');
  auto admins_sid = static_cast<PSID>(admins_buf.data());
  if (!CreateWellKnownSid(
          WinBuiltinAdministratorsSid, nullptr, admins_sid, &sid_buff_size)) {
    return Status(-1, "CreateWellKnownSid failed");
  }

  std::vector<char> system_buf(sid_buff_size, '\0');
  auto system_sid = static_cast<PSID>(system_buf.data());
  if (!CreateWellKnownSid(
          WinLocalSystemSid, nullptr, system_sid, &sid_buff_size)) {
    return Status(-1, "CreateWellKnownSid failed");
  }

  if (EqualSid(owner, admins_sid) || EqualSid(owner, system_sid)) {
    return Status();
  }

  return Status(1, "Owner is not in Administrators group or Local System");
}

Status PlatformFile::isOwnerCurrentUser() const {
  if (!isValid()) {
    return Status(-1, "Invalid file handle value");
  }

  PSID owner = nullptr;
  PSECURITY_DESCRIPTOR sd = nullptr;
  if (GetSecurityInfo(handle_,
                      SE_FILE_OBJECT,
                      OWNER_SECURITY_INFORMATION,
                      &owner,
                      nullptr,
                      nullptr,
                      nullptr,
                      &sd) != ERROR_SUCCESS) {
    return Status(-1, "GetSecurityInfo failed");
  }

  SecurityDescriptor sd_wrapper(sd);
  return isUserCurrentUser(owner);
}

Status PlatformFile::isExecutable() const {
  return hasAccess(handle_, X_OK);
}