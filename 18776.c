int TestOpenFile(std::wstring path, bool for_write) {
  wchar_t path_expanded[MAX_PATH + 1] = {0};
  DWORD size = ::ExpandEnvironmentStrings(path.c_str(), path_expanded,
                                          MAX_PATH);
  if (!size)
    return sandbox::SBOX_TEST_FAILED_TO_EXECUTE_COMMAND;

  HANDLE file;
  file = ::CreateFile(path_expanded,
                      for_write ? GENERIC_READ | GENERIC_WRITE : GENERIC_READ,
                      FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                      NULL,  // No security attributes.
                      OPEN_EXISTING,
                      FILE_FLAG_BACKUP_SEMANTICS,
                      NULL);  // No template.

  if (INVALID_HANDLE_VALUE != file) {
    ::CloseHandle(file);
    return sandbox::SBOX_TEST_SUCCEEDED;
  } else {
    if (ERROR_ACCESS_DENIED == ::GetLastError()) {
      return sandbox::SBOX_TEST_DENIED;
    } else {
      return sandbox::SBOX_TEST_FAILED_TO_EXECUTE_COMMAND;
    }
  }
}
