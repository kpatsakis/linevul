void DownloadItemImpl::OnDownloadCompleting() {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);

  if (state_ != IN_PROGRESS_INTERNAL)
    return;

  DVLOG(20) << __func__ << "() " << DebugString(true);
  DCHECK(!GetTargetFilePath().empty());
  DCHECK(!IsDangerous());

  DCHECK(download_file_.get());
  DownloadFile::RenameCompletionCallback callback =
      base::Bind(&DownloadItemImpl::OnDownloadRenamedToFinalName,
                 weak_ptr_factory_.GetWeakPtr());
  GetDownloadTaskRunner()->PostTask(
      FROM_HERE,
      base::BindOnce(&DownloadFile::RenameAndAnnotate,
                     base::Unretained(download_file_.get()),
                     GetTargetFilePath(),
                     delegate_->GetApplicationClientIdForFileScanning(),
                     GetURL(), GetReferrerUrl(), callback));
}
