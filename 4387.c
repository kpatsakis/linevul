void GDataCache::SetMountedStateOnUIThread(
    const FilePath& file_path,
    bool to_mount,
    const SetMountedStateCallback& callback) {
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::UI));

  base::PlatformFileError* error =
      new base::PlatformFileError(base::PLATFORM_FILE_OK);
  FilePath* cache_file_path = new FilePath;
  pool_->GetSequencedTaskRunner(sequence_token_)->PostTaskAndReply(
      FROM_HERE,
      base::Bind(&GDataCache::SetMountedState,
                 base::Unretained(this),
                 file_path,
                 to_mount,
                 error,
                 cache_file_path),
      base::Bind(&RunSetMountedStateCallback,
                 callback,
                 base::Owned(error),
                 base::Owned(cache_file_path)));
}
