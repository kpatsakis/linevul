SessionStore::WriteBatch::WriteBatch(
    std::unique_ptr<ModelTypeStore::WriteBatch> batch,
    CommitCallback commit_cb,
    syncer::OnceModelErrorHandler error_handler,
    SyncedSessionTracker* session_tracker)
    : batch_(std::move(batch)),
      commit_cb_(std::move(commit_cb)),
      error_handler_(std::move(error_handler)),
      session_tracker_(session_tracker) {
  DCHECK(batch_);
  DCHECK(commit_cb_);
  DCHECK(error_handler_);
  DCHECK(session_tracker_);
}
