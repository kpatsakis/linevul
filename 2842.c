void NavigationControllerImpl::ReloadInternal(bool check_for_repost,
                                              ReloadType reload_type) {
  if (transient_entry_index_ != -1) {
    NavigationEntryImpl* active_entry =
        NavigationEntryImpl::FromNavigationEntry(GetActiveEntry());
    if (!active_entry)
      return;
    LoadURL(active_entry->GetURL(),
            Referrer(),
            PAGE_TRANSITION_RELOAD,
            active_entry->extra_headers());
    return;
  }

  NavigationEntryImpl* entry = NULL;
  int current_index = -1;

  if (IsInitialNavigation() && pending_entry_) {
    entry = pending_entry_;
    current_index = pending_entry_index_;
  } else {
    DiscardNonCommittedEntriesInternal();
    current_index = GetCurrentEntryIndex();
    if (current_index != -1) {
      entry = NavigationEntryImpl::FromNavigationEntry(
          GetEntryAtIndex(current_index));
    }
  }

  if (!entry)
    return;

  if (g_check_for_repost && check_for_repost &&
      entry->GetHasPostData()) {
    web_contents_->NotifyBeforeFormRepostWarningShow();

    pending_reload_ = reload_type;
    web_contents_->Activate();
    web_contents_->GetDelegate()->ShowRepostFormWarningDialog(web_contents_);
  } else {
    if (!IsInitialNavigation())
      DiscardNonCommittedEntriesInternal();

    SiteInstanceImpl* site_instance = entry->site_instance();
    if (site_instance &&
        site_instance->HasWrongProcessForURL(entry->GetURL())) {
      NavigationEntryImpl* nav_entry = NavigationEntryImpl::FromNavigationEntry(
          CreateNavigationEntry(
              entry->GetURL(), entry->GetReferrer(), entry->GetTransitionType(),
              false, entry->extra_headers(), browser_context_));

      reload_type = NavigationController::NO_RELOAD;

      nav_entry->set_should_replace_entry(true);
      pending_entry_ = nav_entry;
    } else {
      pending_entry_ = entry;
      pending_entry_index_ = current_index;

      pending_entry_->SetTitle(string16());

      pending_entry_->SetTransitionType(PAGE_TRANSITION_RELOAD);
    }

    NavigateToPendingEntry(reload_type);
  }
}
