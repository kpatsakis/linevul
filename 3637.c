void IOThread::EnableSpdy(const std::string& mode) {
  static const char kOff[] = "off";
  static const char kSSL[] = "ssl";
  static const char kDisableSSL[] = "no-ssl";
  static const char kDisablePing[] = "no-ping";
  static const char kExclude[] = "exclude";  // Hosts to exclude
  static const char kDisableCompression[] = "no-compress";
  static const char kDisableAltProtocols[] = "no-alt-protocols";
  static const char kForceAltProtocols[] = "force-alt-protocols";
  static const char kSingleDomain[] = "single-domain";

  static const char kInitialMaxConcurrentStreams[] = "init-max-streams";

  std::vector<std::string> spdy_options;
  base::SplitString(mode, ',', &spdy_options);

  for (std::vector<std::string>::iterator it = spdy_options.begin();
       it != spdy_options.end(); ++it) {
    const std::string& element = *it;
    std::vector<std::string> name_value;
    base::SplitString(element, '=', &name_value);
    const std::string& option =
        name_value.size() > 0 ? name_value[0] : std::string();
    const std::string value =
        name_value.size() > 1 ? name_value[1] : std::string();

    if (option == kOff) {
      net::HttpStreamFactory::set_spdy_enabled(false);
    } else if (option == kDisableSSL) {
      globals_->spdy_default_protocol.set(net::kProtoSPDY3);
      net::HttpStreamFactory::set_force_spdy_over_ssl(false);
      net::HttpStreamFactory::set_force_spdy_always(true);
    } else if (option == kSSL) {
      globals_->spdy_default_protocol.set(net::kProtoSPDY3);
      net::HttpStreamFactory::set_force_spdy_over_ssl(true);
      net::HttpStreamFactory::set_force_spdy_always(true);
    } else if (option == kDisablePing) {
      globals_->enable_spdy_ping_based_connection_checking.set(false);
    } else if (option == kExclude) {
      net::HttpStreamFactory::add_forced_spdy_exclusion(value);
    } else if (option == kDisableCompression) {
      globals_->enable_spdy_compression.set(false);
    } else if (option == kDisableAltProtocols) {
      net::HttpStreamFactory::set_use_alternate_protocols(false);
    } else if (option == kForceAltProtocols) {
      net::PortAlternateProtocolPair pair;
      pair.port = 443;
      pair.protocol = net::NPN_SPDY_3;
      net::HttpServerPropertiesImpl::ForceAlternateProtocol(pair);
    } else if (option == kSingleDomain) {
      DVLOG(1) << "FORCING SINGLE DOMAIN";
      globals_->force_spdy_single_domain.set(true);
    } else if (option == kInitialMaxConcurrentStreams) {
      int streams;
      if (base::StringToInt(value, &streams))
        globals_->initial_max_spdy_concurrent_streams.set(streams);
    } else if (option.empty() && it == spdy_options.begin()) {
      continue;
    } else {
      LOG(DFATAL) << "Unrecognized spdy option: " << option;
    }
  }
}
