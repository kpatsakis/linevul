  size_t GetIndependentHistogramCount() {
    HistogramFlattenerDeltaRecorder flattener;
    base::HistogramSnapshotManager snapshot_manager(&flattener);
    SystemProfileProto profile_proto;
    if (!provider()->ProvideIndependentMetrics(&profile_proto,
                                               &snapshot_manager)) {
      return 0;
    }
    return flattener.GetRecordedDeltaHistogramNames().size();
  }
