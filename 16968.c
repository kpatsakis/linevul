void TabStrip::FileSupported(const GURL& url, bool supported) {
  if (drop_info_.get() && drop_info_->url == url)
    drop_info_->file_supported = supported;
}
