void FileAPIMessageFilter::DidGetMetadata(
    int request_id,
    base::PlatformFileError result,
    const base::PlatformFileInfo& info,
    const FilePath& platform_path) {
  if (result == base::PLATFORM_FILE_OK)
    Send(new FileSystemMsg_DidReadMetadata(request_id, info, platform_path));
  else
    Send(new FileSystemMsg_DidFail(request_id, result));
  UnregisterOperation(request_id);
}
