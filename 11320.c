void DownloadItemImpl::InterruptAndDiscardPartialState(
    DownloadInterruptReason reason) {
  InterruptWithPartialState(0, std::unique_ptr<crypto::SecureHash>(), reason);
}
