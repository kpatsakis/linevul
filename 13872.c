EntryImpl* LeakEntryImpl(scoped_refptr<EntryImpl> entry) {
  if (entry)
    entry->AddRef();
  return entry.get();
}
