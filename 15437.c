void AppCacheUpdateJob::OnDestructionImminent(AppCacheHost* host) {
  auto found = pending_master_entries_.find(host->pending_master_entry_url());
  CHECK(found != pending_master_entries_.end());
  PendingHosts& hosts = found->second;
  auto it = std::find(hosts.begin(), hosts.end(), host);
  CHECK(it != hosts.end());
  hosts.erase(it);
}
