GDataEntry* GDataDirectory::FindChild(
    const FilePath::StringType& file_name) const {
  GDataFileCollection::const_iterator it = child_files_.find(file_name);
  if (it != child_files_.end())
    return it->second;

  GDataDirectoryCollection::const_iterator itd =
      child_directories_.find(file_name);
  if (itd != child_directories_.end())
    return itd->second;

  return NULL;
}
