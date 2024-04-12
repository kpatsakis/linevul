void Browser::DidNavigateMainFramePostCommit(WebContents* web_contents) {
  if (web_contents == chrome::GetActiveWebContents(this))
    UpdateBookmarkBarState(BOOKMARK_BAR_STATE_CHANGE_TAB_STATE);
}
