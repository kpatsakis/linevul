void DownloadManagerImpl::OpenDownload(download::DownloadItemImpl* download) {
  int num_unopened = 0;
  for (const auto& it : downloads_) {
    download::DownloadItemImpl* item = it.second.get();
    if ((item->GetState() == download::DownloadItem::COMPLETE) &&
        !item->GetOpened())
      ++num_unopened;
  }
  download::RecordOpensOutstanding(num_unopened);

  if (delegate_)
    delegate_->OpenDownload(download);
}
