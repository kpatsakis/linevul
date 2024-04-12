void WebstoreStandaloneInstaller::AbortInstall() {
  callback_.Reset();
  if (webstore_data_fetcher_) {
    webstore_data_fetcher_.reset();
    scoped_active_install_.reset();
    Release();  // Matches the AddRef in BeginInstall.
  }
}
