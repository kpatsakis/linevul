std::unique_ptr<BlobDataSnapshot> BlobStorageContext::CreateSnapshot(
    const std::string& uuid) {
  std::unique_ptr<BlobDataSnapshot> result;
  BlobEntry* entry = registry_.GetEntry(uuid);
  if (entry->status() != BlobStatus::DONE)
    return result;

  std::unique_ptr<BlobDataSnapshot> snapshot(new BlobDataSnapshot(
      uuid, entry->content_type(), entry->content_disposition()));
  snapshot->items_.reserve(entry->items().size());
  for (const auto& shareable_item : entry->items()) {
    snapshot->items_.push_back(shareable_item->item());
  }
  memory_controller_.NotifyMemoryItemsUsed(entry->items());
  return snapshot;
}
