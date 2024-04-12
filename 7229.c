void SyncBackendHost::Core::NotifyPassphraseAccepted(
    const std::string& bootstrap_token) {
  if (!host_ || !host_->frontend_)
    return;

  DCHECK_EQ(MessageLoop::current(), host_->frontend_loop_);

  processing_passphrase_ = false;
  host_->PersistEncryptionBootstrapToken(bootstrap_token);
  host_->frontend_->OnPassphraseAccepted();
}
