void NavigationControllerImpl::DiscardNonCommittedEntriesInternal() {
  DiscardPendingEntry(false);
  DiscardTransientEntry();
}
