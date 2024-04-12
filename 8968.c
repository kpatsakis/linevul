void OfflinePageModelImpl::SavePage(
    const SavePageParams& save_page_params,
    std::unique_ptr<OfflinePageArchiver> archiver,
    const SavePageCallback& callback) {
  DCHECK(is_loaded_);

  if (!OfflinePageModel::CanSaveURL(save_page_params.url)) {
    InformSavePageDone(callback, SavePageResult::SKIPPED,
                       save_page_params.client_id, kInvalidOfflineId);
    return;
  }

  if (!archiver.get()) {
    InformSavePageDone(callback, SavePageResult::CONTENT_UNAVAILABLE,
                       save_page_params.client_id, kInvalidOfflineId);
    return;
  }

  int64_t offline_id = save_page_params.proposed_offline_id;
  if (offline_id == kInvalidOfflineId)
    offline_id = GenerateOfflineId();

  OfflinePageArchiver::CreateArchiveParams create_archive_params;
  create_archive_params.remove_popup_overlay = save_page_params.is_background;
  create_archive_params.use_page_problem_detectors =
      save_page_params.use_page_problem_detectors;
  archiver->CreateArchive(
      GetArchiveDirectory(save_page_params.client_id.name_space),
      create_archive_params,
      base::Bind(&OfflinePageModelImpl::OnCreateArchiveDone,
                 weak_ptr_factory_.GetWeakPtr(), save_page_params, offline_id,
                 GetCurrentTime(), callback));
  pending_archivers_.push_back(std::move(archiver));
}
