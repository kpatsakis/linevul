bool DirectoryExists(const std::wstring& path) {
  DWORD file_attributes = ::GetFileAttributes(path.c_str());
  if (file_attributes == INVALID_FILE_ATTRIBUTES)
    return false;
  return (file_attributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
}
