void OfflinePageModelImpl::DoDeletePagesByOfflineId(
    const std::vector<int64_t>& offline_ids,
    const DeletePageCallback& callback) {
  DCHECK(is_loaded_);

  std::vector<base::FilePath> paths_to_delete;
  for (const auto& offline_id : offline_ids) {
    auto iter = offline_pages_.find(offline_id);
    if (iter != offline_pages_.end()) {
      paths_to_delete.push_back(iter->second.file_path);
    }
  }

  if (paths_to_delete.empty()) {
    InformDeletePageDone(callback, DeletePageResult::SUCCESS);
    return;
  }

  archive_manager_->DeleteMultipleArchives(
      paths_to_delete,
      base::Bind(&OfflinePageModelImpl::OnDeleteArchiveFilesDone,
                 weak_ptr_factory_.GetWeakPtr(), offline_ids, callback));
}
