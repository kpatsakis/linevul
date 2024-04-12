void GDataFileSystem::OnMarkDirtyInCacheCompleteForOpenFile(
    const OpenFileCallback& callback,
    GDataFileError error,
    const std::string& resource_id,
    const std::string& md5,
    const FilePath& cache_file_path) {
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::UI));

  if (!callback.is_null())
    callback.Run(error, cache_file_path);
}
