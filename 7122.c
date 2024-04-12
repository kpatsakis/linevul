IndexedDBObjectStoreMetadata IndexedDBDatabase::RemoveObjectStore(
    int64_t object_store_id) {
  auto it = metadata_.object_stores.find(object_store_id);
  CHECK(it != metadata_.object_stores.end());
  IndexedDBObjectStoreMetadata metadata = std::move(it->second);
  metadata_.object_stores.erase(it);
  return metadata;
}
