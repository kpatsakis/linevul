void DownloadManagerImpl::CreateSavePackageDownloadItemWithId(
    const base::FilePath& main_file_path,
    const GURL& page_url,
    const std::string& mime_type,
    std::unique_ptr<DownloadRequestHandleInterface> request_handle,
    const DownloadItemImplCreated& item_created,
    uint32_t id) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  DCHECK_NE(content::DownloadItem::kInvalidId, id);
  DCHECK(!base::ContainsKey(downloads_, id));
  DownloadItemImpl* download_item = item_factory_->CreateSavePageItem(
      this, id, main_file_path, page_url, mime_type, std::move(request_handle));
  downloads_[download_item->GetId()] = base::WrapUnique(download_item);
  DCHECK(!base::ContainsKey(downloads_by_guid_, download_item->GetGuid()));
  downloads_by_guid_[download_item->GetGuid()] = download_item;
  for (auto& observer : observers_)
    observer.OnDownloadCreated(this, download_item);
  if (!item_created.is_null())
    item_created.Run(download_item);
}
