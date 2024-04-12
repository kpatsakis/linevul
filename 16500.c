bool HostCache::Entry::IsStale(base::TimeTicks now, int network_changes) const {
  EntryStaleness stale;
  stale.expired_by = now - expires_;
  stale.network_changes = network_changes - network_changes_;
  stale.stale_hits = stale_hits_;
  return stale.is_stale();
}
