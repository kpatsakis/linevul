void ChromeDownloadManagerDelegate::RequestConfirmation(
    DownloadItem* download,
    const base::FilePath& suggested_path,
    DownloadConfirmationReason reason,
    const DownloadTargetDeterminerDelegate::ConfirmationCallback& callback) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  DCHECK(!download->IsTransient());

#if defined(OS_ANDROID)
  switch (reason) {
    case DownloadConfirmationReason::NONE:
      NOTREACHED();
      return;

    case DownloadConfirmationReason::TARGET_PATH_NOT_WRITEABLE:
      DownloadManagerService::OnDownloadCanceled(
          download, DownloadController::CANCEL_REASON_NO_EXTERNAL_STORAGE);
      callback.Run(DownloadConfirmationResult::CANCELED, base::FilePath());
      return;

    case DownloadConfirmationReason::NAME_TOO_LONG:
    case DownloadConfirmationReason::TARGET_NO_SPACE:

    case DownloadConfirmationReason::SAVE_AS:
    case DownloadConfirmationReason::PREFERENCE:
      callback.Run(DownloadConfirmationResult::CONTINUE_WITHOUT_CONFIRMATION,
                   suggested_path);
      return;

    case DownloadConfirmationReason::TARGET_CONFLICT:
      if (download->GetWebContents()) {
        android::ChromeDuplicateDownloadInfoBarDelegate::Create(
            InfoBarService::FromWebContents(download->GetWebContents()),
            download, suggested_path, callback);
        return;
      }

    case DownloadConfirmationReason::UNEXPECTED:
      DownloadManagerService::OnDownloadCanceled(
          download,
          DownloadController::CANCEL_REASON_CANNOT_DETERMINE_DOWNLOAD_TARGET);
      callback.Run(DownloadConfirmationResult::CANCELED, base::FilePath());
      return;
  }
#else   // !OS_ANDROID
  DownloadFilePicker::ShowFilePicker(download, suggested_path, callback);
#endif  // !OS_ANDROID
}
