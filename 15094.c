bool Browser::CanCloseWithInProgressDownloads() {
  if (cancel_download_confirmation_state_ != NOT_PROMPTED)
    return cancel_download_confirmation_state_ != WAITING_FOR_RESPONSE;

  int num_downloads_blocking;
  Browser::DownloadClosePreventionType dialog_type =
      OkToCloseWithInProgressDownloads(&num_downloads_blocking);
  if (dialog_type == DOWNLOAD_CLOSE_OK)
    return true;

  cancel_download_confirmation_state_ = WAITING_FOR_RESPONSE;
  window_->ConfirmBrowserCloseWithPendingDownloads(
      num_downloads_blocking,
      dialog_type,
      false,
      base::Bind(&Browser::InProgressDownloadResponse,
                 weak_factory_.GetWeakPtr()));

  return false;
}
