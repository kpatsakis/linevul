bool BrowserCommandController::IsCommandEnabled(int id) const {
  return command_updater_.IsCommandEnabled(id);
}
