void OfflinePageModelImpl::MarkPageAccessedWhenLoadDone(int64_t offline_id) {
  DCHECK(is_loaded_);

  auto iter = offline_pages_.find(offline_id);
  if (iter == offline_pages_.end())
    return;

  OfflinePageItem offline_page_item = iter->second;

  ReportPageHistogramsAfterAccess(offline_page_item, GetCurrentTime());

  offline_page_item.last_access_time = GetCurrentTime();
  offline_page_item.access_count++;

  std::vector<OfflinePageItem> items = {offline_page_item};
  store_->UpdateOfflinePages(
      items, base::Bind(&OfflinePageModelImpl::OnMarkPageAccesseDone,
                        weak_ptr_factory_.GetWeakPtr(), offline_page_item));
}
