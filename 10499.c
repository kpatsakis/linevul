void BrowserCommandController::TabRestoreServiceChanged(
    sessions::TabRestoreService* service) {
  UpdateTabRestoreCommandState();
}
