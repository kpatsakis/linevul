DownloadControllerBase* DownloadControllerBase::Get() {
  base::AutoLock lock(g_download_controller_lock_.Get());
  if (!DownloadControllerBase::download_controller_)
    download_controller_ = DownloadController::GetInstance();
  return DownloadControllerBase::download_controller_;
}
