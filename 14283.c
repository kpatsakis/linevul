void ChromeDownloadManagerDelegate::CheckDownloadUrl(
    DownloadItem* download,
    const base::FilePath& suggested_path,
    const CheckDownloadUrlCallback& callback) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);

#if defined(FULL_SAFE_BROWSING)
  safe_browsing::DownloadProtectionService* service =
      GetDownloadProtectionService();
  if (service) {
    bool is_content_check_supported =
        service->IsSupportedDownload(*download, suggested_path);
    DVLOG(2) << __func__ << "() Start SB URL check for download = "
             << download->DebugString(false);
    service->CheckDownloadUrl(download,
                              base::Bind(&CheckDownloadUrlDone, callback,
                                         is_content_check_supported));
    return;
  }
#endif
  callback.Run(content::DOWNLOAD_DANGER_TYPE_NOT_DANGEROUS);
}
