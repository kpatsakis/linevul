void JingleSessionManager::Init(
    const std::string& local_jid,
    SignalStrategy* signal_strategy,
    Listener* listener,
    crypto::RSAPrivateKey* private_key,
    const std::string& certificate,
    bool allow_nat_traversal) {
  DCHECK(CalledOnValidThread());

  DCHECK(signal_strategy);
  DCHECK(listener);

  local_jid_ = local_jid;
  signal_strategy_ = signal_strategy;
  listener_ = listener;
  private_key_.reset(private_key);
  certificate_ = certificate;
  allow_nat_traversal_ = allow_nat_traversal;

  if (!network_manager_.get()) {
    VLOG(1) << "Creating talk_base::NetworkManager.";
    network_manager_.reset(new talk_base::BasicNetworkManager());
  }
  if (!socket_factory_.get()) {
    VLOG(1) << "Creating talk_base::BasicPacketSocketFactory.";
    socket_factory_.reset(new talk_base::BasicPacketSocketFactory(
        talk_base::Thread::Current()));
  }


  int port_allocator_flags = cricket::PORTALLOCATOR_DISABLE_TCP;

  if (allow_nat_traversal) {
    http_port_allocator_ = new cricket::HttpPortAllocator(
        network_manager_.get(), socket_factory_.get(), "transp2");
    port_allocator_.reset(http_port_allocator_);
  } else {
    port_allocator_flags |= cricket::PORTALLOCATOR_DISABLE_STUN |
        cricket::PORTALLOCATOR_DISABLE_RELAY;
    port_allocator_.reset(
        new cricket::BasicPortAllocator(
            network_manager_.get(), socket_factory_.get()));
  }
  port_allocator_->set_flags(port_allocator_flags);

  cricket_session_manager_.reset(
      new cricket::SessionManager(port_allocator_.get()));
  cricket_session_manager_->AddClient(kChromotingXmlNamespace, this);

  jingle_signaling_connector_.reset(new JingleSignalingConnector(
      signal_strategy_, cricket_session_manager_.get()));

  if (allow_nat_traversal) {
    jingle_info_request_.reset(new JingleInfoRequest(signal_strategy_));
    jingle_info_request_->Send(base::Bind(
        &JingleSessionManager::OnJingleInfo, base::Unretained(this)));
  } else {
    listener_->OnSessionManagerInitialized();
  }
}
