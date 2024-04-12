  void TestGetCacheState(const std::string& resource_id, const std::string& md5,
                         base::PlatformFileError expected_error,
                         int expected_cache_state, GDataFile* expected_file) {
    expected_error_ = expected_error;
    expected_cache_state_ = expected_cache_state;

    file_system_->GetCacheState(resource_id, md5,
        base::Bind(&GDataFileSystemTest::VerifyGetCacheState,
                   base::Unretained(this)));

    RunAllPendingForIO();
  }
