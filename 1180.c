void ChromeDownloadManagerDelegate::ReturnNextId(
    const content::DownloadIdCallback& callback) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  DCHECK(!profile_->IsOffTheRecord());
  DCHECK_NE(content::DownloadItem::kInvalidId, next_download_id_);
  callback.Run(next_download_id_++);
}
