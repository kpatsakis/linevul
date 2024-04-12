void GDataFileSystem::OnGetAboutResource(
    const GetAvailableSpaceCallback& callback,
    GDataErrorCode status,
    scoped_ptr<base::Value> resource_json) {
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::UI));
  DCHECK(!callback.is_null());

  GDataFileError error = util::GDataToGDataFileError(status);
  if (error != GDATA_FILE_OK) {
    callback.Run(error, -1, -1);
    return;
  }

  scoped_ptr<AboutResource> about;
  if (resource_json.get())
    about = AboutResource::CreateFrom(*resource_json);

  if (!about.get()) {
    callback.Run(GDATA_FILE_ERROR_FAILED, -1, -1);
    return;
  }

  callback.Run(GDATA_FILE_OK,
               about->quota_bytes_total(),
               about->quota_bytes_used());
}
