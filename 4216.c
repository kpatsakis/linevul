void RecordParallelizableDownloadStats(
    size_t bytes_downloaded_with_parallel_streams,
    base::TimeDelta time_with_parallel_streams,
    size_t bytes_downloaded_without_parallel_streams,
    base::TimeDelta time_without_parallel_streams,
    bool uses_parallel_requests) {
  RecordParallelizableDownloadAverageStats(
      bytes_downloaded_with_parallel_streams +
          bytes_downloaded_without_parallel_streams,
      time_with_parallel_streams + time_without_parallel_streams);

  int64_t bandwidth_without_parallel_streams = 0;
  if (bytes_downloaded_without_parallel_streams > 0) {
    bandwidth_without_parallel_streams = CalculateBandwidthBytesPerSecond(
        bytes_downloaded_without_parallel_streams,
        time_without_parallel_streams);
    if (uses_parallel_requests) {
      RecordBandwidthMetric(
          "Download.ParallelizableDownloadBandwidth."
          "WithParallelRequestsSingleStream",
          bandwidth_without_parallel_streams);
    } else {
      RecordBandwidthMetric(
          "Download.ParallelizableDownloadBandwidth."
          "WithoutParallelRequests",
          bandwidth_without_parallel_streams);
    }
  }

  if (!uses_parallel_requests)
    return;

  base::TimeDelta time_saved;
  if (bytes_downloaded_with_parallel_streams > 0) {
    int64_t bandwidth_with_parallel_streams = CalculateBandwidthBytesPerSecond(
        bytes_downloaded_with_parallel_streams, time_with_parallel_streams);
    RecordBandwidthMetric(
        "Download.ParallelizableDownloadBandwidth."
        "WithParallelRequestsMultipleStreams",
        bandwidth_with_parallel_streams);
    if (bandwidth_without_parallel_streams > 0) {
      time_saved = base::TimeDelta::FromMilliseconds(
                       1000.0 * bytes_downloaded_with_parallel_streams /
                       bandwidth_without_parallel_streams) -
                   time_with_parallel_streams;
    }
  }

  int kMillisecondsPerHour =
      base::checked_cast<int>(base::Time::kMillisecondsPerSecond * 60 * 60);
  if (time_saved >= base::TimeDelta()) {
    UMA_HISTOGRAM_CUSTOM_COUNTS(
        "Download.EstimatedTimeSavedWithParallelDownload",
        time_saved.InMilliseconds(), 0, kMillisecondsPerHour, 50);
  } else {
    UMA_HISTOGRAM_CUSTOM_COUNTS(
        "Download.EstimatedTimeWastedWithParallelDownload",
        -time_saved.InMilliseconds(), 0, kMillisecondsPerHour, 50);
  }
}
