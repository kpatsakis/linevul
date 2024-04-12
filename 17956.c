void OfflinePageModelTaskified::OnCreateArchiveDone(
    const SavePageCallback& callback,
    OfflinePageItem proposed_page,
    OfflinePageArchiver* archiver,
    ArchiverResult archiver_result,
    const GURL& saved_url,
    const base::FilePath& file_path,
    const base::string16& title,
    int64_t file_size,
    const std::string& digest) {
  pending_archivers_.erase(
      std::find_if(pending_archivers_.begin(), pending_archivers_.end(),
                   [archiver](const std::unique_ptr<OfflinePageArchiver>& a) {
                     return a.get() == archiver;
                   }));

  if (archiver_result != ArchiverResult::SUCCESSFULLY_CREATED) {
    SavePageResult result = ArchiverResultToSavePageResult(archiver_result);
    InformSavePageDone(callback, result, proposed_page);
    return;
  }
  if (proposed_page.url != saved_url) {
    DVLOG(1) << "Saved URL does not match requested URL.";
    InformSavePageDone(callback, SavePageResult::ARCHIVE_CREATION_FAILED,
                       proposed_page);
    return;
  }
  proposed_page.file_path = file_path;
  proposed_page.file_size = file_size;
  proposed_page.title = title;
  proposed_page.digest = digest;
  AddPage(proposed_page,
          base::Bind(&OfflinePageModelTaskified::OnAddPageForSavePageDone,
                     weak_ptr_factory_.GetWeakPtr(), callback, proposed_page));
}
