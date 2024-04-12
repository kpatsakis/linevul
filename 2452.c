void Browser::TabReplacedAt(TabStripModel* tab_strip_model,
                            TabContentsWrapper* old_contents,
                            TabContentsWrapper* new_contents,
                            int index) {
  TabDetachedAtImpl(old_contents, index, DETACH_TYPE_REPLACE);
  TabInsertedAt(new_contents, index,
                (index == tab_handler_->GetTabStripModel()->active_index()));

  int entry_count = new_contents->controller().entry_count();
  if (entry_count > 0) {
    new_contents->controller().NotifyEntryChanged(
        new_contents->controller().GetEntryAtIndex(entry_count - 1),
        entry_count - 1);
  }

  SessionService* session_service =
      SessionServiceFactory::GetForProfile(profile());
  if (session_service) {
    session_service->TabRestored(
        new_contents, tab_handler_->GetTabStripModel()->IsTabPinned(index));
  }

  DevToolsManager* devtools_manager = DevToolsManager::GetInstance();
  if (devtools_manager)  // NULL in unit tests.
    devtools_manager->TabReplaced(old_contents->tab_contents(),
                                  new_contents->tab_contents());
}
