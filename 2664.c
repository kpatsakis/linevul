void DownloadItemImpl::SetLastAccessTime(base::Time last_access_time) {
  last_access_time_ = last_access_time;
  UpdateObservers();
}
