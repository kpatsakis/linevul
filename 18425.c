void ProfileSyncService::UpdateLastSyncedTime() {
  last_synced_time_ = base::Time::Now();
  sync_prefs_.SetLastSyncedTime(last_synced_time_);
}
