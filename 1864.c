  virtual webkit_glue::ResourceLoaderBridge::Peer* OnRequestComplete(
      webkit_glue::ResourceLoaderBridge::Peer* current_peer,
      ResourceType::Type resource_type,
      int error_code) {
    if (!weak_factory_.HasWeakPtrs()) {
      MessageLoop::current()->PostDelayedTask(
         FROM_HERE,
         base::Bind(&RendererResourceDelegate::InformHostOfCacheStats,
                    weak_factory_.GetWeakPtr()),
         base::TimeDelta::FromMilliseconds(kCacheStatsDelayMS));
    }

    if (error_code == net::ERR_ABORTED) {
      return NULL;
    }

    return SecurityFilterPeer::CreateSecurityFilterPeerForDeniedRequest(
        resource_type, current_peer, error_code);
  }
