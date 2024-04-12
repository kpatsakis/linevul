void GDataFileSystem::OnCommitDirtyInCacheCompleteForCloseFile(
    const FileOperationCallback& callback,
    GDataFileError error,
    const std::string& resource_id,
    const std::string& md5) {
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::UI));

  if (!callback.is_null())
    callback.Run(error);
}
