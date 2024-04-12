void GDataCache::PinOnUIThread(const std::string& resource_id,
                               const std::string& md5,
                               const CacheOperationCallback& callback) {
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::UI));

  base::PlatformFileError* error =
      new base::PlatformFileError(base::PLATFORM_FILE_OK);
  pool_->GetSequencedTaskRunner(sequence_token_)->PostTaskAndReply(
      FROM_HERE,
      base::Bind(&GDataCache::Pin,
                 base::Unretained(this),
                 resource_id,
                 md5,
                 GDataCache::FILE_OPERATION_MOVE,
                 error),
      base::Bind(&GDataCache::OnPinned,
                 ui_weak_ptr_,
                 base::Owned(error),
                 resource_id,
                 md5,
                 callback));
}
