void BrowserCommandController::UpdateCommandsForBookmarkEditing() {
  command_updater_.UpdateCommandEnabled(IDC_BOOKMARK_PAGE,
                                        CanBookmarkCurrentPage(browser_));
  command_updater_.UpdateCommandEnabled(IDC_BOOKMARK_ALL_TABS,
                                        CanBookmarkAllTabs(browser_));
  command_updater_.UpdateCommandEnabled(IDC_PIN_TO_START_SCREEN,
                                        true);
}
