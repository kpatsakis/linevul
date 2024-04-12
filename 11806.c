void ChromeDownloadManagerDelegate::OnDownloadTargetDetermined(
    int32_t download_id,
    const content::DownloadTargetCallback& callback,
    std::unique_ptr<DownloadTargetInfo> target_info) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  DownloadItem* item = download_manager_->GetDownload(download_id);
  if (item) {
    if (!target_info->target_path.empty() &&
        IsOpenInBrowserPreferreredForFile(target_info->target_path) &&
        target_info->is_filetype_handled_safely)
      DownloadItemModel(item).SetShouldPreferOpeningInBrowser(true);

#if defined(OS_LINUX)
    if (item->GetOriginalMimeType() == "application/x-x509-user-cert")
      DownloadItemModel(item).SetShouldPreferOpeningInBrowser(true);
#endif

    DownloadItemModel(item).SetDangerLevel(target_info->danger_level);
  }
  if (ShouldBlockFile(target_info->danger_type)) {
    target_info->result = content::DOWNLOAD_INTERRUPT_REASON_FILE_BLOCKED;
    target_info->danger_type = content::DOWNLOAD_DANGER_TYPE_NOT_DANGEROUS;
  }

  callback.Run(target_info->target_path, target_info->target_disposition,
               target_info->danger_type, target_info->intermediate_path,
               target_info->result);
}
