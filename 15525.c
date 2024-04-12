void ChromeDownloadManagerDelegate::CheckClientDownloadDone(
    uint32_t download_id,
    safe_browsing::DownloadCheckResult result) {
  DownloadItem* item = download_manager_->GetDownload(download_id);
  if (!item || (item->GetState() != DownloadItem::IN_PROGRESS))
    return;

  DVLOG(2) << __func__ << "() download = " << item->DebugString(false)
           << " verdict = " << static_cast<int>(result);
  if (item->GetDangerType() == content::DOWNLOAD_DANGER_TYPE_NOT_DANGEROUS ||
      item->GetDangerType() ==
      content::DOWNLOAD_DANGER_TYPE_MAYBE_DANGEROUS_CONTENT) {
    content::DownloadDangerType danger_type =
        content::DOWNLOAD_DANGER_TYPE_NOT_DANGEROUS;
    switch (result) {
      case safe_browsing::DownloadCheckResult::UNKNOWN:
        if (DownloadItemModel(item).GetDangerLevel() !=
            DownloadFileType::NOT_DANGEROUS) {
          danger_type = content::DOWNLOAD_DANGER_TYPE_DANGEROUS_FILE;
          UMA_HISTOGRAM_ENUMERATION("Download.DangerousFile.Reason",
                                    SB_RETURNS_UNKOWN,
                                    DANGEROUS_FILE_REASON_MAX);
        }
        break;
      case safe_browsing::DownloadCheckResult::SAFE:
        if (DownloadItemModel(item).GetDangerLevel() ==
            DownloadFileType::DANGEROUS) {
          danger_type = content::DOWNLOAD_DANGER_TYPE_DANGEROUS_FILE;
          UMA_HISTOGRAM_ENUMERATION("Download.DangerousFile.Reason",
                                    SB_RETURNS_SAFE, DANGEROUS_FILE_REASON_MAX);
        }
        break;
      case safe_browsing::DownloadCheckResult::DANGEROUS:
        danger_type = content::DOWNLOAD_DANGER_TYPE_DANGEROUS_CONTENT;
        break;
      case safe_browsing::DownloadCheckResult::UNCOMMON:
        danger_type = content::DOWNLOAD_DANGER_TYPE_UNCOMMON_CONTENT;
        break;
      case safe_browsing::DownloadCheckResult::DANGEROUS_HOST:
        danger_type = content::DOWNLOAD_DANGER_TYPE_DANGEROUS_HOST;
        break;
      case safe_browsing::DownloadCheckResult::POTENTIALLY_UNWANTED:
        danger_type = content::DOWNLOAD_DANGER_TYPE_POTENTIALLY_UNWANTED;
        break;
    }
    DCHECK_NE(danger_type,
              content::DOWNLOAD_DANGER_TYPE_MAYBE_DANGEROUS_CONTENT);

    if (danger_type != content::DOWNLOAD_DANGER_TYPE_NOT_DANGEROUS) {
      if (ShouldBlockFile(danger_type)) {
        item->OnContentCheckCompleted(
            content::DOWNLOAD_DANGER_TYPE_NOT_DANGEROUS,
            content::DOWNLOAD_INTERRUPT_REASON_FILE_BLOCKED);
      } else {
        item->OnContentCheckCompleted(danger_type,
                                      content::DOWNLOAD_INTERRUPT_REASON_NONE);
      }
    }
  }

  SafeBrowsingState* state = static_cast<SafeBrowsingState*>(
      item->GetUserData(&kSafeBrowsingUserDataKey));
  state->CompleteDownload();
}
