  PersistentHistogramAllocatorTest()
      : statistics_recorder_(StatisticsRecorder::CreateTemporaryForTesting()) {
    CreatePersistentHistogramAllocator();
  }
