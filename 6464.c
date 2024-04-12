void FileAPIMessageFilter::OnWrite(
    int request_id,
    const GURL& path,
    const GURL& blob_url,
    int64 offset) {
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::IO));
  if (!request_context_) {
    NOTREACHED();
    return;
  }

  FileSystemURL url(path);
  base::PlatformFileError error;
  if (!HasPermissionsForFile(url, kWriteFilePermissions, &error)) {
    Send(new FileSystemMsg_DidFail(request_id, error));
    return;
  }

  FileSystemOperation* operation = GetNewOperation(url, request_id);
  if (!operation)
    return;
  operation->Write(
      request_context_, url, blob_url, offset,
      base::Bind(&FileAPIMessageFilter::DidWrite, this, request_id));
}
