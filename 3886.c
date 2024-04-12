void DownloadManagerImpl::OnHistoryNextIdRetrived(uint32_t next_id) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  is_history_download_id_retrieved_ = true;
  if (next_id == download::DownloadItem::kInvalidId)
    next_id++;
  else
    should_persist_new_download_ = true;
  SetNextId(next_id);
}
