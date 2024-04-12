void RenderMessageFilter::AsyncOpenFileOnFileThread(const FilePath& path,
                                                    int flags,
                                                    int message_id,
                                                    int routing_id) {
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::FILE));
  base::PlatformFileError error_code = base::PLATFORM_FILE_OK;
  base::PlatformFile file = base::CreatePlatformFile(
      path, flags, NULL, &error_code);
  IPC::PlatformFileForTransit file_for_transit =
      file != base::kInvalidPlatformFileValue ?
          IPC::GetFileHandleForProcess(file, peer_handle(), true) :
          IPC::InvalidPlatformFileForTransit();

  IPC::Message* reply = new ViewMsg_AsyncOpenFile_ACK(
      routing_id, error_code, file_for_transit, message_id);
  BrowserThread::PostTask(
      BrowserThread::IO, FROM_HERE,
      base::Bind(base::IgnoreResult(&RenderMessageFilter::Send), this, reply));
}
