void DownloadManagerImpl::SetNextId(uint32_t next_id) {
  if (next_id > next_download_id_)
    next_download_id_ = next_id;
  if (!IsNextIdInitialized())
    return;

  for (auto& callback : id_callbacks_)
    std::move(*callback).Run(next_download_id_++);
  id_callbacks_.clear();
}
