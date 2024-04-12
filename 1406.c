void GDataFileSystem::TransferRegularFile(
    const FilePath& local_file_path,
    const FilePath& remote_dest_file_path,
    const FileOperationCallback& callback) {
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::UI));

  GDataFileError* error =
      new GDataFileError(GDATA_FILE_OK);
  int64* file_size = new int64;
  std::string* content_type = new std::string;
  util::PostBlockingPoolSequencedTaskAndReply(
      FROM_HERE,
      blocking_task_runner_,
      base::Bind(&GetLocalFileInfoOnBlockingPool,
                 local_file_path,
                 error,
                 file_size,
                 content_type),
      base::Bind(&GDataFileSystem::StartFileUploadOnUIThread,
                 ui_weak_ptr_,
                 StartFileUploadParams(local_file_path,
                                       remote_dest_file_path,
                                       callback),
                 base::Owned(error),
                 base::Owned(file_size),
                 base::Owned(content_type)));
}
