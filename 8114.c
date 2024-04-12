void Browser::FileSelectedWithExtraInfo(
    const ui::SelectedFileInfo& file_info,
    int index,
    void* params) {
  profile_->set_last_selected_directory(file_info.file_path.DirName());

  const FilePath& path = file_info.local_path;
  GURL file_url = net::FilePathToFileURL(path);

#if defined(OS_CHROMEOS)
  drive::util::ModifyDriveFileResourceUrl(profile_, path, &file_url);
#endif

  if (file_url.is_empty())
    return;

  OpenURL(OpenURLParams(
      file_url, Referrer(), CURRENT_TAB, content::PAGE_TRANSITION_TYPED,
      false));
}
