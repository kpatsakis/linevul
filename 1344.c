bool BookmarksImportFunction::RunImpl() {
  if (!EditBookmarksEnabled())
    return false;
  SelectFile(ui::SelectFileDialog::SELECT_OPEN_FILE);
  return true;
}
