void BrowserCommandController::TabRestoreServiceDestroyed(
    sessions::TabRestoreService* service) {
  service->RemoveObserver(this);
}
