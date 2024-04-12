  void CreateFolderInBob() {
    WriteTransaction trans(FROM_HERE, UNITTEST, directory());
    MutableEntry bob(&trans,
                     syncable::GET_BY_ID,
                     GetOnlyEntryWithName(&trans,
                                          TestIdFactory::root(),
                                          "bob"));
    CHECK(bob.good());

    MutableEntry entry2(&trans, syncable::CREATE, bob.Get(syncable::ID),
                        "bob");
    CHECK(entry2.good());
    entry2.Put(syncable::IS_DIR, true);
    entry2.Put(syncable::IS_UNSYNCED, true);
    entry2.Put(syncable::SPECIFICS, DefaultBookmarkSpecifics());
  }
