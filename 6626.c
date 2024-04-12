void ChromeDownloadManagerDelegate::CheckClientDownloadDone(
    int32 download_id,
    DownloadProtectionService::DownloadCheckResult result) {
  DownloadItem* item = download_manager_->GetActiveDownloadItem(download_id);
  if (!item)
    return;

  VLOG(2) << __FUNCTION__ << "() download = " << item->DebugString(false)
          << " verdict = " << result;
  if (item->GetSafetyState() == DownloadItem::SAFE) {
    switch (result) {
      case DownloadProtectionService::SAFE:
        break;
      case DownloadProtectionService::DANGEROUS:
        item->OnContentCheckCompleted(
            content::DOWNLOAD_DANGER_TYPE_DANGEROUS_CONTENT);
        break;
      case DownloadProtectionService::UNCOMMON:
        item->OnContentCheckCompleted(
            content::DOWNLOAD_DANGER_TYPE_UNCOMMON_CONTENT);
        break;
    }
  }

  SafeBrowsingState* state = static_cast<SafeBrowsingState*>(
      item->GetExternalData(&safe_browsing_id));
  state->SetVerdict(result);
}
