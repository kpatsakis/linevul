content::MockDownloadItem* MockDownloadItemFactory::GetItem(int id) {
  if (items_.find(id) == items_.end())
    return NULL;
  return items_[id];
}
