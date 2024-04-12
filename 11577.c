void GDataFileSystem::RemoveOnUIThread(
    const FilePath& file_path,
    bool is_recursive,
    const FileOperationCallback& callback) {
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::UI));

  directory_service_->GetEntryInfoByPath(
      file_path,
      base::Bind(
          &GDataFileSystem::RemoveOnUIThreadAfterGetEntryInfo,
          ui_weak_ptr_,
          file_path,
          is_recursive,
          callback));
}
