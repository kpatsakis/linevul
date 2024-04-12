std::unique_ptr<BlobDataHandle> BlobStorageContext::GetBlobDataFromPublicURL(
    const GURL& url) {
  std::string uuid;
  BlobEntry* entry = registry_.GetEntryFromURL(url, &uuid);
  if (!entry)
    return nullptr;
  return CreateHandle(uuid, entry);
}
