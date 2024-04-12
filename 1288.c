bool DownloadManagerImpl::IsMostRecentDownloadItemAtFilePath(
    download::DownloadItemImpl* download) {
  return delegate_ ? delegate_->IsMostRecentDownloadItemAtFilePath(download)
                   : false;
}
