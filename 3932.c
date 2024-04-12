bool AddGenericPolicy(sandbox::TargetPolicy* policy) {
  sandbox::ResultCode result;

  result = policy->AddRule(sandbox::TargetPolicy::SUBSYS_FILES,
                           sandbox::TargetPolicy::FILES_ALLOW_ANY,
                           L"\\??\\pipe\\chrome.*");
  if (result != sandbox::SBOX_ALL_OK)
    return false;
  result = policy->AddRule(sandbox::TargetPolicy::SUBSYS_NAMED_PIPES,
                           sandbox::TargetPolicy::NAMEDPIPES_ALLOW_ANY,
                           L"\\\\.\\pipe\\chrome.nacl.*");
  if (result != sandbox::SBOX_ALL_OK)
    return false;
  result = policy->AddRule(sandbox::TargetPolicy::SUBSYS_NAMED_PIPES,
                           sandbox::TargetPolicy::NAMEDPIPES_ALLOW_ANY,
                           L"\\\\.\\pipe\\chrome.sync.*");
  if (result != sandbox::SBOX_ALL_OK)
    return false;

#ifndef NDEBUG
  FilePath app_dir;
  if (!PathService::Get(base::DIR_MODULE, &app_dir))
    return false;

  wchar_t long_path_buf[MAX_PATH];
  DWORD long_path_return_value = GetLongPathName(app_dir.value().c_str(),
                                                 long_path_buf,
                                                 MAX_PATH);
  if (long_path_return_value == 0 || long_path_return_value >= MAX_PATH)
    return false;

  FilePath debug_message(long_path_buf);
  debug_message = debug_message.AppendASCII("debug_message.exe");
  result = policy->AddRule(sandbox::TargetPolicy::SUBSYS_PROCESS,
                           sandbox::TargetPolicy::PROCESS_MIN_EXEC,
                           debug_message.value().c_str());
  if (result != sandbox::SBOX_ALL_OK)
    return false;
#endif  // NDEBUG

  return true;
}
