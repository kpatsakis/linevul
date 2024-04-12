void BrowserCommandController::TabRestoreServiceDestroyed(
    TabRestoreService* service) {
  service->RemoveObserver(this);
}
