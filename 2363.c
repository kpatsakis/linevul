void NavigationControllerImpl::SetPendingEntry(
    std::unique_ptr<NavigationEntryImpl> entry) {
  DiscardNonCommittedEntriesInternal();
  pending_entry_ = entry.release();
  DCHECK_EQ(-1, pending_entry_index_);
  NotificationService::current()->Notify(
      NOTIFICATION_NAV_ENTRY_PENDING,
      Source<NavigationController>(this),
      Details<NavigationEntry>(pending_entry_));
}
