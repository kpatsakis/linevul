ResourceDispatcherHostImpl::IncrementOutstandingRequestsMemory(
    int count,
    const ResourceRequestInfoImpl& info) {
  DCHECK_EQ(1, abs(count));

  OustandingRequestsStats stats = GetOutstandingRequestsStats(info);

  stats.memory_cost += count * info.memory_cost();
  DCHECK_GE(stats.memory_cost, 0);
  UpdateOutstandingRequestsStats(info, stats);

  return stats;
}
