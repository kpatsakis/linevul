void BlobStorageContext::IncrementBlobRefCount(const std::string& uuid) {
  BlobEntry* entry = registry_.GetEntry(uuid);
  DCHECK(entry);
  entry->IncrementRefCount();
}
