void AutomationProvider::ReloadAsync(int tab_handle) {
  if (tab_tracker_->ContainsHandle(tab_handle)) {
    NavigationController* tab = tab_tracker_->GetResource(tab_handle);
    if (!tab) {
      NOTREACHED();
      return;
    }

    const bool check_for_repost = true;
    tab->Reload(check_for_repost);
  }
}
