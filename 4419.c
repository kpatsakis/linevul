void BookmarksIOFunction::SelectFile(ui::SelectFileDialog::Type type) {
  if (!BrowserThread::CurrentlyOn(BrowserThread::FILE)) {
    BrowserThread::PostTask(BrowserThread::FILE, FROM_HERE,
        base::Bind(&BookmarksIOFunction::SelectFile, this, type));
    return;
  }

  base::FilePath default_path;
  if (type == ui::SelectFileDialog::SELECT_SAVEAS_FILE)
    default_path = GetDefaultFilepathForBookmarkExport();
  else
    DCHECK(type == ui::SelectFileDialog::SELECT_OPEN_FILE);

  BrowserThread::PostTask(BrowserThread::UI, FROM_HERE,
      base::Bind(&BookmarksIOFunction::ShowSelectFileDialog, this,
                 type, default_path));
}
