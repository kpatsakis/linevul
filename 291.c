void TabStripModel::NotifyIfActiveTabChanged(TabContents* old_contents,
                                             NotifyTypes notify_types) {
  TabContents* new_contents = GetTabContentsAtImpl(active_index());
  if (old_contents != new_contents) {
    FOR_EACH_OBSERVER(TabStripModelObserver, observers_,
                      ActiveTabChanged(old_contents, new_contents,
                                       active_index(),
                                       notify_types == NOTIFY_USER_GESTURE));
    contents_data_[active_index()]->discarded = false;
  }
}
