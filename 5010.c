void ResourceDispatcherHostImpl::UnregisterDownloadedTempFile(
    int child_id, int request_id) {
  DeletableFilesMap& map = registered_temp_files_[child_id];
  DeletableFilesMap::iterator found = map.find(request_id);
  if (found == map.end())
    return;

  map.erase(found);

}
