void GDataFileSystem::OnCloseFileFinished(
    const FilePath& file_path,
    const FileOperationCallback& callback,
    GDataFileError result) {
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::UI));

  open_files_.erase(file_path);

  if (!callback.is_null())
    callback.Run(result);
}
