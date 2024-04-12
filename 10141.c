void Browser::DuplicateContentsAt(int index) {
  TabContentsWrapper* contents = GetTabContentsWrapperAt(index);
  CHECK(contents);
  TabContentsWrapper* contents_dupe = contents->Clone();
  TabContents* new_contents = contents_dupe->tab_contents();

  bool pinned = false;
  if (CanSupportWindowFeature(FEATURE_TABSTRIP)) {
    int index = tab_handler_->GetTabStripModel()->
        GetIndexOfTabContents(contents);
    pinned = tab_handler_->GetTabStripModel()->IsTabPinned(index);
    int add_types = TabStripModel::ADD_SELECTED |
        TabStripModel::ADD_INHERIT_GROUP |
        (pinned ? TabStripModel::ADD_PINNED : 0);
    tab_handler_->GetTabStripModel()->InsertTabContentsAt(index + 1,
                                                          contents_dupe,
                                                          add_types);
  } else {
    Browser* browser = NULL;
    if (type_ & TYPE_APP) {
      CHECK((type_ & TYPE_POPUP) == 0);
      CHECK(type_ != TYPE_APP_PANEL);
      browser = Browser::CreateForApp(app_name_, gfx::Size(), profile_,
                                      false);
    } else if (type_ == TYPE_POPUP) {
      browser = Browser::CreateForType(TYPE_POPUP, profile_);
    }

    BrowserWindow* new_window = browser->window();
    new_window->SetBounds(gfx::Rect(new_window->GetRestoredBounds().origin(),
                          window()->GetRestoredBounds().size()));

    browser->window()->Show();

    browser->AddTab(contents_dupe, PageTransition::LINK);
  }

  if (profile_->HasSessionService()) {
    SessionService* session_service = profile_->GetSessionService();
    if (session_service)
      session_service->TabRestored(&new_contents->controller(), pinned);
  }
}
