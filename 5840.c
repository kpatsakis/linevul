  CacheThread() : base::Thread("CacheThread_BlockFile") {
    CHECK(
        StartWithOptions(base::Thread::Options(base::MessageLoop::TYPE_IO, 0)));
  }
