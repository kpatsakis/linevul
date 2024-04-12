void NavigationControllerImpl::PruneAllButVisible() {
  PruneAllButVisibleInternal();

  DCHECK_NE(-1, last_committed_entry_index_);

  NavigationEntryImpl* entry =
      NavigationEntryImpl::FromNavigationEntry(GetActiveEntry());
  web_contents_->SetHistoryLengthAndPrune(
      entry->site_instance(), 0, entry->GetPageID());
}
