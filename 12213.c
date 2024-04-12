void MemBackendImpl::OnEntryInserted(MemEntryImpl* entry) {
  lru_list_.Append(entry);
}
