void DownloadItemImpl::SetFullPath(const FilePath& new_path) {
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::UI));
  VLOG(20) << __FUNCTION__ << "()"
           << " new_path = \"" << new_path.value() << "\""
           << " " << DebugString(true);
  DCHECK(!new_path.empty());
  current_path_ = new_path;

  bound_net_log_.AddEvent(
      net::NetLog::TYPE_DOWNLOAD_ITEM_RENAMED,
      base::Bind(&download_net_logs::ItemRenamedCallback,
                 &current_path_, &new_path));
}
