void GDataFileSystem::Remove(const FilePath& file_path,
    bool is_recursive,
    const FileOperationCallback& callback) {
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::UI) ||
         BrowserThread::CurrentlyOn(BrowserThread::IO));
  RunTaskOnUIThread(base::Bind(&GDataFileSystem::RemoveOnUIThread,
                               ui_weak_ptr_,
                               file_path,
                               is_recursive,
                               CreateRelayCallback(callback)));
}
