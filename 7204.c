void GDataFileSystem::OnUpdatedFileUploaded(
    const FileOperationCallback& callback,
    GDataFileError error,
    scoped_ptr<UploadFileInfo> upload_file_info) {
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::UI));
  DCHECK(upload_file_info.get());

  if (error != GDATA_FILE_OK) {
    if (!callback.is_null())
      callback.Run(error);
    return;
  }

  AddUploadedFile(UPLOAD_EXISTING_FILE,
                  upload_file_info->gdata_path.DirName(),
                  upload_file_info->entry.Pass(),
                  upload_file_info->file_path,
                  GDataCache::FILE_OPERATION_MOVE,
                  base::Bind(&OnAddUploadFileCompleted, callback, error));
}
