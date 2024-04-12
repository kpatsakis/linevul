void ResourceMessageFilter::OnGetFileModificationTime(const FilePath& path,
                                                      IPC::Message* reply_msg) {
  if (!ChildProcessSecurityPolicy::GetInstance()->CanUploadFile(id(), path)) {
    ViewHostMsg_GetFileModificationTime::WriteReplyParams(reply_msg,
                                                          base::Time());
    Send(reply_msg);
    return;
  }

  ChromeThread::PostTask(
      ChromeThread::FILE, FROM_HERE,
      NewRunnableMethod(
          this, &ResourceMessageFilter::OnGetFileInfoOnFileThread,
          path, reply_msg, &WriteFileModificationTime));
}
