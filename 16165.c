void Browser::OpenCreateShortcutsDialog() {
  UserMetrics::RecordAction(UserMetricsAction("CreateShortcut"), profile_);
#if defined(OS_WIN) || defined(OS_LINUX)
  TabContentsWrapper* current_tab = GetSelectedTabContentsWrapper();
  DCHECK(current_tab &&
      web_app::IsValidUrl(current_tab->tab_contents()->GetURL())) <<
          "Menu item should be disabled.";

  NavigationEntry* entry = current_tab->controller().GetLastCommittedEntry();
  if (!entry)
    return;

  DCHECK(pending_web_app_action_ == NONE);
  pending_web_app_action_ = CREATE_SHORTCUT;

  current_tab->extension_tab_helper()->GetApplicationInfo(entry->page_id());
#else
  NOTIMPLEMENTED();
#endif
}
