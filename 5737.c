  void VerifyTestBookmarkDataInEntry(Entry* entry) {
    const sync_pb::EntitySpecifics& specifics = entry->Get(syncable::SPECIFICS);
    EXPECT_TRUE(specifics.has_bookmark());
    EXPECT_EQ("PNG", specifics.bookmark().favicon());
    EXPECT_EQ("http://demo/", specifics.bookmark().url());
  }
