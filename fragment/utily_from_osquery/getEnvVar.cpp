from osquery

boost::optional<std::string> getEnvVar(const std::string& name) {
  const auto kInitialBufferSize = 1024;
  std::vector<char> buf;
  buf.assign(kInitialBufferSize, '\0');

  auto value_len =
      ::GetEnvironmentVariableA(name.c_str(), buf.data(), kInitialBufferSize);
  if (value_len == 0) {
    return boost::none;
  }

  // It is always possible that between the first GetEnvironmentVariableA call
  // and this one, a change was made to our target environment variable that
  // altered the size. Currently, we ignore this scenario and fail if the
  // returned size is greater than what we expect.
  if (value_len > kInitialBufferSize) {
    buf.assign(value_len, '\0');
    value_len = ::GetEnvironmentVariableA(name.c_str(), buf.data(), value_len);
    if (value_len == 0 || value_len > buf.size()) {
      // The size returned is greater than the size we expected. Currently, we
      // will not deal with this scenario and just return as if an error has
      // occurred.
      return boost::none;
    }
  }

  return std::string(buf.data(), value_len);
}