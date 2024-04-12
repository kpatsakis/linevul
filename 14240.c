std::string GetBuildIDForModule(HMODULE module_handle) {
  GUID guid;
  DWORD age;
  win::PEImage(module_handle).GetDebugId(&guid, &age);
  const int kGUIDSize = 39;
  std::wstring build_id;
  int result =
      ::StringFromGUID2(guid, WriteInto(&build_id, kGUIDSize), kGUIDSize);
  if (result != kGUIDSize)
    return std::string();
  RemoveChars(build_id, L"{}-", &build_id);
  build_id += StringPrintf(L"%d", age);
  return WideToUTF8(build_id);
}
