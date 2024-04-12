void DownloadManagerImpl::ImportInProgressDownloads(uint32_t id) {
  for (auto& download : in_progress_downloads_) {
    auto item = std::move(download);
    if (item->GetId() == download::DownloadItem::kInvalidId) {
      item->SetDownloadId(id++);
      next_download_id_++;
      if (!should_persist_new_download_)
        in_progress_manager_->RemoveInProgressDownload(item->GetGuid());
    }
    item->SetDelegate(this);
    DownloadItemUtils::AttachInfo(item.get(), GetBrowserContext(), nullptr);
    OnDownloadCreated(std::move(item));
  }
  in_progress_downloads_.clear();

  OnDownloadManagerInitialized();
}
