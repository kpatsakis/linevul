void GetFileContentByPath(
    const DriveFileStreamReader::DriveFileSystemGetter& file_system_getter,
    const base::FilePath& drive_file_path,
    const GetFileContentInitializedCallback& initialized_callback,
    const google_apis::GetContentCallback& get_content_callback,
    const FileOperationCallback& completion_callback) {
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::IO));

  BrowserThread::PostTask(
      BrowserThread::UI,
      FROM_HERE,
      base::Bind(&GetFileContentByPathOnUIThread,
                 file_system_getter,
                 drive_file_path,
                 google_apis::CreateRelayCallback(initialized_callback),
                 google_apis::CreateRelayCallback(get_content_callback),
                 google_apis::CreateRelayCallback(completion_callback)));
}
