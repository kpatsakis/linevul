void NavigationController::GoToOffset(int offset) {
  int index = (transient_entry_index_ != -1) ?
                  transient_entry_index_ + offset :
                  last_committed_entry_index_ + offset;
  if (index < 0 || index >= entry_count())
    return;

   GoToIndex(index);
 }
