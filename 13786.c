  void TestUnpin(
      const std::string& resource_id,
      const std::string& md5,
      base::PlatformFileError expected_error,
      int expected_cache_state,
      GDataRootDirectory::CacheSubDirectoryType expected_sub_dir_type) {
    expected_error_ = expected_error;
    expected_cache_state_ = expected_cache_state;
    expected_sub_dir_type_ = expected_sub_dir_type;

    file_system_->Unpin(resource_id, md5,
        base::Bind(&GDataFileSystemTest::VerifyCacheFileState,
                   base::Unretained(this)));

    RunAllPendingForIO();
  }
