void DownloadRequestLimiter::SetOnCanDownloadDecidedCallbackForTesting(
    Callback callback) {
  on_can_download_decided_callback_ = callback;
}
