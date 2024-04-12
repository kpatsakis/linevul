  ~ExpectNoWriteBarrierFires() {
    EXPECT_TRUE(marking_worklist_->IsGlobalEmpty());
    for (const auto& pair : headers_) {
      EXPECT_EQ(pair.second, pair.first->IsMarked());
      pair.first->Unmark();
    }
  }
