TabContents* Browser::AddRestoredTab(
    const std::vector<TabNavigation>& navigations,
    int tab_index,
    int selected_navigation,
    const std::string& extension_app_id,
    bool select,
    bool pin,
    bool from_last_session,
    SessionStorageNamespace* session_storage_namespace) {
  TabContentsWrapper* wrapper = TabContentsFactory(profile(), NULL,
      MSG_ROUTING_NONE,
      GetSelectedTabContents(),
      session_storage_namespace);
  TabContents* new_tab = wrapper->tab_contents();
  new_tab->SetExtensionAppById(extension_app_id);
  new_tab->controller().RestoreFromState(navigations, selected_navigation,
                                         from_last_session);

  bool really_pin =
      (pin && tab_index == tabstrip_model()->IndexOfFirstNonMiniTab());
  tab_handler_->GetTabStripModel()->InsertTabContentsAt(
      tab_index, wrapper,
      select ? TabStripModel::ADD_SELECTED : TabStripModel::ADD_NONE);
  if (really_pin)
    tab_handler_->GetTabStripModel()->SetTabPinned(tab_index, true);
  if (select) {
    window_->Activate();
  } else {
    new_tab->view()->SizeContents(window_->GetRestoredBounds().size());
    new_tab->HideContents();
  }
  if (profile_->HasSessionService()) {
    SessionService* session_service = profile_->GetSessionService();
    if (session_service)
      session_service->TabRestored(&new_tab->controller(), really_pin);
  }
  return new_tab;
}
