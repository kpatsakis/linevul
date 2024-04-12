  void VerifyPrefSync() {
    ASSERT_TRUE(BooleanPrefMatches(prefs::kShowHomeButton));
    ChangeBooleanPref(0, prefs::kShowHomeButton);
    ASSERT_TRUE(GetClient(0)->AwaitMutualSyncCycleCompletion(GetClient(1)));
    ASSERT_TRUE(BooleanPrefMatches(prefs::kShowHomeButton));
  }
