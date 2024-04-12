void DownloadItemImpl::DestinationCompleted(
    int64_t total_bytes,
    std::unique_ptr<crypto::SecureHash> secure_hash) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  DCHECK(state_ == TARGET_PENDING_INTERNAL || state_ == IN_PROGRESS_INTERNAL);
  DVLOG(20) << __func__ << "() download=" << DebugString(true);

  OnAllDataSaved(total_bytes, std::move(secure_hash));
  MaybeCompleteDownload();
}
