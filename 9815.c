  void ExpectLocalOrderIsByServerId() {
    ScopedDirLookup dir(syncdb_.manager(), syncdb_.name());
    EXPECT_TRUE(dir.good());
    ReadTransaction trans(FROM_HERE, dir);
    Id null_id;
    Entry low(&trans, GET_BY_ID, low_id_);
    Entry mid(&trans, GET_BY_ID, mid_id_);
    Entry high(&trans, GET_BY_ID, high_id_);
    EXPECT_TRUE(low.good());
    EXPECT_TRUE(mid.good());
    EXPECT_TRUE(high.good());
    EXPECT_TRUE(low.Get(PREV_ID) == null_id);
    EXPECT_TRUE(mid.Get(PREV_ID) == low_id_);
    EXPECT_TRUE(high.Get(PREV_ID) == mid_id_);
    EXPECT_TRUE(high.Get(NEXT_ID) == null_id);
    EXPECT_TRUE(mid.Get(NEXT_ID) == high_id_);
    EXPECT_TRUE(low.Get(NEXT_ID) == mid_id_);
  }
