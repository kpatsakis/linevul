void ChromeNetworkDelegate::SetEnableClientHints() {
  client_hints_.reset(new ClientHints());
  client_hints_->Init();
}
