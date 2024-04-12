void DownloadItemImpl::OffThreadCancel(DownloadFileManager* file_manager) {
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::UI));
  request_handle_->CancelRequest();

  BrowserThread::PostTask(
      BrowserThread::FILE, FROM_HERE,
      base::Bind(&DownloadFileManager::CancelDownload,
                 file_manager, download_id_));
}
