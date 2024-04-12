HKEY GetHKEYFromString(const std::wstring &name) {
  if (L"HKLM" == name)
    return HKEY_LOCAL_MACHINE;
  else if (L"HKCR" == name)
    return HKEY_CLASSES_ROOT;
  else if (L"HKCC" == name)
    return HKEY_CURRENT_CONFIG;
  else if (L"HKCU" == name)
    return HKEY_CURRENT_USER;
  else if (L"HKU" == name)
    return HKEY_USERS;

  return NULL;
}
