void AllDownloadsCompleteObserver::OnDownloadCreated(
    DownloadManager* manager, DownloadItem* item) {
  if (pre_download_ids_.find(item->GetId()) == pre_download_ids_.end() &&
      item->GetState() == DownloadItem::IN_PROGRESS) {
    item->AddObserver(this);
    pending_downloads_.insert(item);
  }
}
