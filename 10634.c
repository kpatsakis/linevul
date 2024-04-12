void OfflinePageModelImpl::OnPagesFoundWithSameURL(
    const OfflinePageItem& offline_page,
    size_t pages_allowed,
    const MultipleOfflinePageItemResult& items) {
  std::vector<OfflinePageItem> pages_to_delete;
  for (const auto& item : items) {
    if (item.offline_id != offline_page.offline_id &&
        item.client_id.name_space == offline_page.client_id.name_space) {
      pages_to_delete.push_back(item);
    }
  }
  if (pages_to_delete.size() >= pages_allowed) {
    sort(pages_to_delete.begin(), pages_to_delete.end(),
         [](const OfflinePageItem& a, const OfflinePageItem& b) -> bool {
           return a.last_access_time < b.last_access_time;
         });
    pages_to_delete.resize(pages_to_delete.size() - pages_allowed + 1);
  }
  std::vector<int64_t> page_ids_to_delete;
  for (const auto& item : pages_to_delete)
    page_ids_to_delete.push_back(item.offline_id);
  DeletePagesByOfflineId(
      page_ids_to_delete,
      base::Bind(&OfflinePageModelImpl::OnDeleteOldPagesWithSameURL,
                 weak_ptr_factory_.GetWeakPtr()));
}
