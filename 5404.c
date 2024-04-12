void SelectFileDialogImpl::MultiFilesSelected(
    const std::vector<FilePath>& selected_files,
    void* params,
    RunState run_state) {
  if (listener_)
    listener_->MultiFilesSelected(selected_files, params);
  EndRun(run_state);
}
