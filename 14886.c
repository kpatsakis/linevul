bool FileUtilProxy::GetFileInfo(
    scoped_refptr<MessageLoopProxy> message_loop_proxy,
    const FilePath& file_path,
    GetFileInfoCallback* callback) {
  return Start(FROM_HERE, message_loop_proxy, new RelayGetFileInfo(
               file_path, callback));
}
