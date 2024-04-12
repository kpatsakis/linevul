  void AddEntries(StorageType type, UsageTracker* tracker) {
    std::map<std::string, int64> host_usage;
    tracker->GetCachedHostsUsage(&host_usage);
    for (std::map<std::string, int64>::const_iterator iter = host_usage.begin();
         iter != host_usage.end();
         ++iter) {
      entries_.push_back(UsageInfo(iter->first, type, iter->second));
    }
    if (--remaining_trackers_ == 0)
      CallCompleted();
  }
