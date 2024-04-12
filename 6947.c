int DownloadManagerImpl::InProgressCount() const {
  int count = 0;
  for (const auto& it : downloads_) {
    if (it.second->GetState() == DownloadItem::IN_PROGRESS)
      ++count;
  }
  return count;
}
