bool DownloadManagerImpl::IsNextIdInitialized() const {
  return is_history_download_id_retrieved_ && in_progress_cache_initialized_;
}
