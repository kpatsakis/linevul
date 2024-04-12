void AppListController::FreeAnyKeepAliveForView() {
  if (keep_alive_)
    keep_alive_.reset(NULL);
}
