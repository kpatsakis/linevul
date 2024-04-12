int BackendImpl::CheckAllEntries() {
  int num_dirty = 0;
  int num_entries = 0;
  DCHECK(mask_ < std::numeric_limits<uint32_t>::max());
  for (unsigned int i = 0; i <= mask_; i++) {
    Addr address(data_->table[i]);
    if (!address.is_initialized())
      continue;
    for (;;) {
      scoped_refptr<EntryImpl> cache_entry;
      int ret = NewEntry(address, &cache_entry);
      if (ret) {
        STRESS_NOTREACHED();
        return ret;
      }

      if (cache_entry->dirty())
        num_dirty++;
      else if (CheckEntry(cache_entry.get()))
        num_entries++;
      else
        return ERR_INVALID_ENTRY;

      DCHECK_EQ(i, cache_entry->entry()->Data()->hash & mask_);
      address.set_value(cache_entry->GetNextAddress());
      if (!address.is_initialized())
        break;
    }
  }

  Trace("CheckAllEntries End");
  if (num_entries + num_dirty != data_->header.num_entries) {
    LOG(ERROR) << "Number of entries " << num_entries << " " << num_dirty <<
                  " " << data_->header.num_entries;
    DCHECK_LT(num_entries, data_->header.num_entries);
    return ERR_NUM_ENTRIES_MISMATCH;
  }

  return num_dirty;
}
