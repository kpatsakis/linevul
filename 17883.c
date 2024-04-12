void Browser::DidNavigateMainFramePostCommit(TabContents* tab) {
  if (tab == GetSelectedTabContents())
    UpdateBookmarkBarState(BOOKMARK_BAR_STATE_CHANGE_TAB_STATE);
}
