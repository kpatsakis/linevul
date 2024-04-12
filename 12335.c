void GDataFileSystem::OnGetAvailableSpace(
    const GetAvailableSpaceCallback& callback,
    GDataErrorCode status,
    scoped_ptr<base::Value> data) {
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::UI));
  DCHECK(!callback.is_null());

  GDataFileError error = util::GDataToGDataFileError(status);
  if (error != GDATA_FILE_OK) {
    callback.Run(error, -1, -1);
    return;
  }

  scoped_ptr<AccountMetadataFeed> feed;
  if (data.get())
    feed = AccountMetadataFeed::CreateFrom(*data);
  if (!feed.get()) {
    callback.Run(GDATA_FILE_ERROR_FAILED, -1, -1);
    return;
  }

  callback.Run(GDATA_FILE_OK,
               feed->quota_bytes_total(),
               feed->quota_bytes_used());
}
