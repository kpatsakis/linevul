DriveFileStreamReader::DriveFileStreamReader(
    const DriveFileSystemGetter& drive_file_system_getter)
    : drive_file_system_getter_(drive_file_system_getter),
      ALLOW_THIS_IN_INITIALIZER_LIST(weak_ptr_factory_(this)) {
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::IO));
}
