  static void ExpectWindowCountAfterDownload(size_t expected) {
    EXPECT_EQ(expected, chrome::GetTotalBrowserCount());
  }
