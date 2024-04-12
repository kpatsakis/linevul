  void TestLoadMetadataFromCache() {
    file_system_->LoadRootFeedFromCache(
        false,     // load_from_server
        FilePath(FILE_PATH_LITERAL("drive")),
        base::Bind(&GDataFileSystemTest::OnExpectToFindEntry,
                   FilePath(FILE_PATH_LITERAL("drive"))));
    BrowserThread::GetBlockingPool()->FlushForTesting();
    message_loop_.RunAllPending();
  }
