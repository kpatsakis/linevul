  void Restart() {
    DCHECK(IsLoaderInterceptionEnabled());
    if (!default_loader_used_ ||
        (base::FeatureList::IsEnabled(network::features::kNetworkService) &&
         !IsURLHandledByDefaultLoader(resource_request_->url))) {
      url_loader_.reset();
    }
    interceptor_index_ = 0;
    received_response_ = false;
    MaybeStartLoader(nullptr /* interceptor */,
                     {} /* single_request_handler */);
  }
