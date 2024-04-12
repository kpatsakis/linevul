FilePath DownloadItemImpl::GetFileNameToReportUser() const {
  if (!display_name_.empty())
    return display_name_;
  return target_path_.BaseName();
}
