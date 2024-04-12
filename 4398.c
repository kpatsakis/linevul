void Browser::ActiveTabChanged(WebContents* old_contents,
                               WebContents* new_contents,
                               int index,
                               int reason) {
  content::RecordAction(UserMetricsAction("ActiveTabChanged"));

  UpdateBookmarkBarState(BOOKMARK_BAR_STATE_CHANGE_TAB_SWITCH);

  window_->OnActiveTabChanged(old_contents, new_contents, index, reason);

  exclusive_access_manager_->OnTabDetachedFromView(old_contents);

  if (g_browser_process->GetTabManager()->IsTabDiscarded(new_contents))
    chrome::Reload(this, WindowOpenDisposition::CURRENT_TAB);

  if (chrome_updater_factory_.HasWeakPtrs() && old_contents)
    ProcessPendingUIUpdates();

  UpdateToolbar((reason & CHANGE_REASON_REPLACED) == 0);

  if (search::IsInstantExtendedAPIEnabled())
    search_delegate_->OnTabActivated(new_contents);

  command_controller_->LoadingStateChanged(new_contents->IsLoading(), true);

  command_controller_->TabStateChanged();

  StatusBubble* status_bubble = GetStatusBubble();
  if (status_bubble) {
    status_bubble->Hide();

    status_bubble->SetStatus(CoreTabHelper::FromWebContents(
        tab_strip_model_->GetActiveWebContents())->GetStatusText());
  }

  if (HasFindBarController()) {
    find_bar_controller_->ChangeWebContents(new_contents);
    find_bar_controller_->find_bar()->MoveWindowIfNecessary(gfx::Rect());
  }

  SessionService* session_service =
      SessionServiceFactory::GetForProfileIfExisting(profile_);
  if (session_service && !tab_strip_model_->closing_all()) {
    session_service->SetSelectedTabInWindow(session_id(),
                                            tab_strip_model_->active_index());
    SessionTabHelper* session_tab_helper =
        SessionTabHelper::FromWebContents(new_contents);
    session_service->SetLastActiveTime(session_id(),
                                       session_tab_helper->session_id(),
                                       base::TimeTicks::Now());
  }

  if (instant_controller_)
    instant_controller_->ActiveTabChanged();

  SearchTabHelper::FromWebContents(new_contents)->OnTabActivated();
}
