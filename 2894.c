bool FileUtilProxy::Touch(
    scoped_refptr<MessageLoopProxy> message_loop_proxy,
    const FilePath& file_path,
    const base::Time& last_access_time,
    const base::Time& last_modified_time,
    StatusCallback* callback) {
  return Start(FROM_HERE, message_loop_proxy,
               new RelayTouchFilePath(file_path, last_access_time,
                                      last_modified_time, callback));
}
