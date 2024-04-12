void ProcessCommitResponseCommand::ModelChangingExecuteImpl(
    SyncSession* session) {
  ProcessCommitResponse(session);
  ExtensionsActivityMonitor* monitor = session->context()->extensions_monitor();
  if (session->status_controller()->HasBookmarkCommitActivity() &&
      session->status_controller()->syncer_status()
          .num_successful_bookmark_commits == 0) {
    monitor->PutRecords(session->extensions_activity());
    session->mutable_extensions_activity()->clear();
  }
}
