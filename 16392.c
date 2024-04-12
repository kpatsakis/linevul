void GDataDirectory::RemoveChildDirectories() {
  for (GDataDirectoryCollection::iterator iter = child_directories_.begin();
       iter != child_directories_.end(); ++iter) {
    GDataDirectory* dir = iter->second;
    dir->RemoveChildren();
    if (directory_service_)
      directory_service_->RemoveEntryFromResourceMap(dir);
  }
  STLDeleteValues(&child_directories_);
  child_directories_.clear();
}
