void ChromotingHost::OnStateChange(
    SignalStrategy::StatusObserver::State state) {
  DCHECK(context_->network_message_loop()->BelongsToCurrentThread());

  if (state == SignalStrategy::StatusObserver::CONNECTED) {
    LOG(INFO) << "Host connected as " << local_jid_;

    protocol::JingleSessionManager* server =
        new protocol::JingleSessionManager(context_->network_message_loop());
    server->set_allow_local_ips(true);

    HostKeyPair key_pair;
    CHECK(key_pair.Load(config_))
        << "Failed to load server authentication data";

    server->Init(local_jid_, signal_strategy_.get(), this,
                 key_pair.CopyPrivateKey(), key_pair.GenerateCertificate(),
                 allow_nat_traversal_);

    session_manager_.reset(server);

    for (StatusObserverList::iterator it = status_observers_.begin();
         it != status_observers_.end(); ++it) {
      (*it)->OnSignallingConnected(signal_strategy_.get(), local_jid_);
    }
  } else if (state == SignalStrategy::StatusObserver::CLOSED) {
    LOG(INFO) << "Host disconnected from talk network.";
    for (StatusObserverList::iterator it = status_observers_.begin();
         it != status_observers_.end(); ++it) {
      (*it)->OnSignallingDisconnected();
    }
  }
}
