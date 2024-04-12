void NavigationControllerImpl::InsertOrReplaceEntry(NavigationEntryImpl* entry,
                                                    bool replace) {
  DCHECK(entry->GetTransitionType() != PAGE_TRANSITION_AUTO_SUBFRAME);

  const NavigationEntryImpl* const pending_entry =
      (pending_entry_index_ == -1) ?
          pending_entry_ : entries_[pending_entry_index_].get();
  if (pending_entry)
    entry->set_unique_id(pending_entry->GetUniqueID());

  DiscardNonCommittedEntriesInternal();

  int current_size = static_cast<int>(entries_.size());

  if (current_size > 0) {
    if (replace)
      --last_committed_entry_index_;

    int num_pruned = 0;
    while (last_committed_entry_index_ < (current_size - 1)) {
      num_pruned++;
      entries_.pop_back();
      current_size--;
    }
    if (num_pruned > 0)  // Only notify if we did prune something.
      NotifyPrunedEntries(this, false, num_pruned);
  }

  PruneOldestEntryIfFull();

  entries_.push_back(linked_ptr<NavigationEntryImpl>(entry));
  last_committed_entry_index_ = static_cast<int>(entries_.size()) - 1;

  web_contents_->UpdateMaxPageID(entry->GetPageID());
}
