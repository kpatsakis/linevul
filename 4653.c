int BackendImpl::SyncDoomEntry(const std::string& key) {
  if (disabled_)
    return net::ERR_FAILED;

  scoped_refptr<EntryImpl> entry = OpenEntryImpl(key);
  if (!entry)
    return net::ERR_FAILED;

  entry->DoomImpl();
  return net::OK;
}
