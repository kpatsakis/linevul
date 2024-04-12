void Browser::TabDetachedAtImpl(TabContentsWrapper* contents, int index,
                                DetachType type) {
  if (type == DETACH_TYPE_DETACH) {
    if (contents == GetSelectedTabContentsWrapper())
      window_->GetLocationBar()->SaveStateToContents(contents->tab_contents());

    if (!tab_handler_->GetTabStripModel()->closing_all())
      SyncHistoryWithTabs(0);
  }

  SetAsDelegate(contents, NULL);
  RemoveScheduledUpdatesFor(contents->tab_contents());

  if (find_bar_controller_.get() &&
      index == tab_handler_->GetTabStripModel()->selected_index()) {
    find_bar_controller_->ChangeTabContents(NULL);
  }

  if (is_attempting_to_close_browser_) {
    ClearUnloadState(contents->tab_contents(), false);
  }

  registrar_.Remove(this, NotificationType::TAB_CONTENTS_DISCONNECTED,
                    Source<TabContentsWrapper>(contents));
}
