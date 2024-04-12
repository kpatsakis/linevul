 void DevToolsSession::SetBrowserOnly(bool browser_only) {
  browser_only_ = browser_only;
  dispatcher_->setFallThroughForNotFound(!browser_only);
}
