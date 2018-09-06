Status windowsGetFileVersion(const std::string& path, std::string& rVersion) {
  DWORD handle = 0;
  auto verSize = GetFileVersionInfoSize(path.c_str(), &handle);
  auto verInfo = std::make_unique<BYTE[]>(verSize);
  if (verInfo == nullptr) {
    return Status(1, "Failed to malloc for version info");
  }
  auto err = GetFileVersionInfo(path.c_str(), handle, verSize, verInfo.get());
  if (err == 0) {
    return Status(GetLastError(), "Failed to get file version info");
  }
  VS_FIXEDFILEINFO* pFileInfo = nullptr;
  UINT verInfoSize = 0;
  err = VerQueryValue(
      verInfo.get(), TEXT("\\"), (LPVOID*)&pFileInfo, &verInfoSize);
  if (err == 0) {
    return Status(GetLastError(), "Failed to query version value");
  }
  rVersion =
      std::to_string((pFileInfo->dwProductVersionMS >> 16 & 0xffff)) + "." +
      std::to_string((pFileInfo->dwProductVersionMS >> 0 & 0xffff)) + "." +
      std::to_string((pFileInfo->dwProductVersionLS >> 16 & 0xffff)) + "." +
      std::to_string((pFileInfo->dwProductVersionLS >> 0 & 0xffff));
  return Status();
}