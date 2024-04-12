bool DownloadItemImpl::ShouldOpenFileBasedOnExtension() {
  return delegate_->ShouldOpenFileBasedOnExtension(GetUserVerifiedFilePath());
}
