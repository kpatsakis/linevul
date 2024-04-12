void SessionService::CommitPendingCloses() {
  for (PendingTabCloseIDs::iterator i = pending_tab_close_ids_.begin();
       i != pending_tab_close_ids_.end(); ++i) {
    ScheduleCommand(CreateTabClosedCommand(*i));
  }
  pending_tab_close_ids_.clear();

  for (PendingWindowCloseIDs::iterator i = pending_window_close_ids_.begin();
       i != pending_window_close_ids_.end(); ++i) {
    ScheduleCommand(CreateWindowClosedCommand(*i));
  }
  pending_window_close_ids_.clear();
}
