std::string SessionStore::WriteBatch::PutAndUpdateTracker(
    const sync_pb::SessionSpecifics& specifics,
    base::Time modification_time) {
  UpdateTrackerWithSpecifics(specifics, modification_time, session_tracker_);
  return PutWithoutUpdatingTracker(specifics);
}
