void WebContentsImpl::OnDidDownloadImage(
    int id,
    int http_status_code,
    const GURL& image_url,
    int requested_size,
    const std::vector<SkBitmap>& bitmaps) {
  ImageDownloadMap::iterator iter = image_download_map_.find(id);
  if (iter == image_download_map_.end()) {
    return;
  }
  if (!iter->second.is_null()) {
    iter->second.Run(id, http_status_code, image_url, requested_size, bitmaps);
  }
  image_download_map_.erase(id);
}
