int ResourceDispatcherHost::GetOutstandingRequestsMemoryCost(
    int child_id) const {
  OutstandingRequestsMemoryCostMap::const_iterator entry =
      outstanding_requests_memory_cost_map_.find(child_id);
  return (entry == outstanding_requests_memory_cost_map_.end()) ?
      0 : entry->second;
}
