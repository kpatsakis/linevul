URLPatternSet PermissionsData::GetEffectiveHostPermissions() const {
  base::AutoLock auto_lock(runtime_lock_);
  URLPatternSet effective_hosts = active_permissions_unsafe_->effective_hosts();
  for (const auto& val : tab_specific_permissions_)
    effective_hosts.AddPatterns(val.second->effective_hosts());
  return effective_hosts;
}
