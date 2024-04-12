  void ExpectUnsyncedDeletion() {
    EXPECT_EQ(metahandle_, GetMetahandleOfTag());
    EXPECT_TRUE(Get(metahandle_, IS_DEL));
    EXPECT_FALSE(Get(metahandle_, SERVER_IS_DEL));
    EXPECT_TRUE(Get(metahandle_, IS_UNSYNCED));
    EXPECT_FALSE(Get(metahandle_, IS_UNAPPLIED_UPDATE));
    EXPECT_LT(0, Get(metahandle_, BASE_VERSION));
    EXPECT_LT(0, Get(metahandle_, SERVER_VERSION));
  }
