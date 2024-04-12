bool VolumeSupportsACLs(const wchar_t* any_path) {
  wchar_t expand[MAX_PATH +1];
  DWORD len =::ExpandEnvironmentStringsW(any_path, expand, _countof(expand));
  if (0 == len) return false;
  if (len >  _countof(expand)) return false;
  if (!::PathStripToRootW(expand)) return false;
  DWORD fs_flags = 0;
  if (!::GetVolumeInformationW(expand, NULL, 0, 0, NULL, &fs_flags, NULL, 0))
    return false;
  if (fs_flags & FILE_PERSISTENT_ACLS) return true;
  return false;
}
