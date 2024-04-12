void OfflinePageModelImpl::DeleteOrphanedArchives(
    const std::set<base::FilePath>& archive_paths) {
  std::set<base::FilePath> orphaned_archive_set(archive_paths);
  for (const auto& id_page_pair : offline_pages_)
    orphaned_archive_set.erase(id_page_pair.second.file_path);

  if (orphaned_archive_set.empty())
    return;

  std::vector<base::FilePath> orphaned_archives(orphaned_archive_set.begin(),
                                                orphaned_archive_set.end());
  archive_manager_->DeleteMultipleArchives(
      orphaned_archives,
      base::Bind(&OfflinePageModelImpl::OnDeleteOrphanedArchivesDone,
                 weak_ptr_factory_.GetWeakPtr(), orphaned_archives));
}
