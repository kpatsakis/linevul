  virtual void CreateEntry(const AddEntriesMessage::TestEntryInfo& entry) {
    CreateEntryImpl(entry, root_path().AppendASCII(entry.target_path));
  }
