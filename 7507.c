  int64 CreateUnsyncedDirectory(const string& entry_name,
      const syncable::Id& id) {
    ScopedDirLookup dir(syncdb_.manager(), syncdb_.name());
    EXPECT_TRUE(dir.good());
    WriteTransaction wtrans(FROM_HERE, UNITTEST, dir);
    MutableEntry entry(&wtrans, syncable::CREATE, wtrans.root_id(),
                       entry_name);
    EXPECT_TRUE(entry.good());
    entry.Put(syncable::IS_UNSYNCED, true);
    entry.Put(syncable::IS_DIR, true);
    entry.Put(syncable::SPECIFICS, DefaultBookmarkSpecifics());
    entry.Put(syncable::BASE_VERSION, id.ServerKnows() ? 1 : 0);
    entry.Put(syncable::ID, id);
    return entry.Get(META_HANDLE);
  }
