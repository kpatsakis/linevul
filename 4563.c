bool DownloadItemImpl::CanShowInFolder() {
  return CanOpenDownload() && !GetFullPath().empty();
}
