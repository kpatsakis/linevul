void NavigationControllerImpl::FinishRestore(int selected_index,
                                             RestoreType type) {
  DCHECK(selected_index >= 0 && selected_index < GetEntryCount());
  ConfigureEntriesForRestore(&entries_, type);

  SetMaxRestoredPageID(static_cast<int32>(GetEntryCount()));

  last_committed_entry_index_ = selected_index;
 }
