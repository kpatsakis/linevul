void GDataFileSystem::OnFileDownloaded(
    const GetFileFromCacheParams& params,
    GDataErrorCode status,
    const GURL& content_url,
    const FilePath& downloaded_file_path) {
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::UI));

  if (status == GDATA_CANCELLED) {
    cache_->GetCacheEntryOnUIThread(
        params.resource_id,
        params.md5,
        base::Bind(&GDataFileSystem::UnpinIfPinned,
                   ui_weak_ptr_,
                   params.resource_id,
                   params.md5));
  }

  bool* has_enough_space = new bool(false);
  util::PostBlockingPoolSequencedTaskAndReply(
      FROM_HERE,
      blocking_task_runner_,
      base::Bind(&GDataCache::FreeDiskSpaceIfNeededFor,
                 base::Unretained(cache_),
                 0,
                 has_enough_space),
      base::Bind(&GDataFileSystem::OnFileDownloadedAndSpaceChecked,
                 ui_weak_ptr_,
                 params,
                 status,
                 content_url,
                 downloaded_file_path,
                 base::Owned(has_enough_space)));
}
