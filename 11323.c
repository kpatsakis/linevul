void NavigationRequest::OnResponseStarted(
    const scoped_refptr<network::ResourceResponse>& response,
    network::mojom::URLLoaderClientEndpointsPtr url_loader_client_endpoints,
    std::unique_ptr<NavigationData> navigation_data,
    const GlobalRequestID& request_id,
    bool is_download,
    NavigationDownloadPolicy download_policy,
    bool is_stream,
    base::Optional<SubresourceLoaderParams> subresource_loader_params) {
  is_download_ = is_download && IsNavigationDownloadAllowed(download_policy);
  is_stream_ = is_stream;
  request_id_ = request_id;

  if (is_download &&
      download_policy == NavigationDownloadPolicy::kDisallowOpenerCrossOrigin) {
    content::RenderFrameHost* rfh = frame_tree_node_->current_frame_host();
    rfh->AddMessageToConsole(
        CONSOLE_MESSAGE_LEVEL_ERROR,
        base::StringPrintf(
            "Navigating a cross-origin opener to a download (%s) is "
            "deprecated, see "
            "https://www.chromestatus.com/feature/5742188281462784.",
            navigation_handle_->GetURL().spec().c_str()));
    GetContentClient()->browser()->LogWebFeatureForCurrentPage(
        rfh, blink::mojom::WebFeature::kOpenerNavigationDownloadCrossOrigin);
  }

  if (state_ != STARTED) {
    DEBUG_ALIAS_FOR_GURL(url, navigation_handle_->GetURL());
    base::debug::DumpWithoutCrashing();
  }
  DCHECK_EQ(state_, STARTED);
  DCHECK(response);
  TRACE_EVENT_ASYNC_STEP_INTO0("navigation", "NavigationRequest", this,
                               "OnResponseStarted");
  state_ = RESPONSE_STARTED;

  response_should_be_rendered_ =
      !is_download_ && (!response->head.headers.get() ||
                        (response->head.headers->response_code() != 204 &&
                         response->head.headers->response_code() != 205));

  if (!response_should_be_rendered_) {
    navigation_handle_->set_net_error_code(net::ERR_ABORTED);
    net_error_ = net::ERR_ABORTED;
  }

  commit_params_.service_worker_provider_id =
      navigation_handle_->service_worker_handle()
          ? navigation_handle_->service_worker_handle()
                ->service_worker_provider_host_id()
          : kInvalidServiceWorkerProviderId;
  commit_params_.appcache_host_id =
      navigation_handle_->appcache_handle()
          ? navigation_handle_->appcache_handle()->appcache_host_id()
          : blink::mojom::kAppCacheNoHostId;

  commit_params_.navigation_timing.fetch_start =
      std::max(commit_params_.navigation_timing.fetch_start,
               response->head.service_worker_ready_time);

  if (commit_params_.was_activated == WasActivatedOption::kUnknown) {
    commit_params_.was_activated = WasActivatedOption::kNo;

    if (navigation_handle_->IsRendererInitiated() &&
        (frame_tree_node_->has_received_user_gesture() ||
         frame_tree_node_->has_received_user_gesture_before_nav()) &&
        ShouldPropagateUserActivation(
            frame_tree_node_->current_origin(),
            url::Origin::Create(navigation_handle_->GetURL()))) {
      commit_params_.was_activated = WasActivatedOption::kYes;
    } else if (((navigation_handle_->HasUserGesture() &&
                 navigation_handle_->IsRendererInitiated()) ||
                navigation_handle_->WasStartedFromContextMenu()) &&
               ShouldPropagateUserActivation(
                   url::Origin::Create(navigation_handle_->GetReferrer().url),
                   url::Origin::Create(navigation_handle_->GetURL()))) {
      commit_params_.was_activated = WasActivatedOption::kYes;
    }
  }

  if (response_should_be_rendered_) {
    render_frame_host_ =
        frame_tree_node_->render_manager()->GetFrameHostForNavigation(*this);
    NavigatorImpl::CheckWebUIRendererDoesNotDisplayNormalURL(
        render_frame_host_, common_params_.url);
  } else {
    render_frame_host_ = nullptr;
  }
  DCHECK(render_frame_host_ || !response_should_be_rendered_);

  if (!browser_initiated_ && render_frame_host_ &&
      render_frame_host_ != frame_tree_node_->current_frame_host()) {
    common_params_.source_location.reset();

    if (!frame_tree_node_->navigator()->GetDelegate()->ShouldTransferNavigation(
            frame_tree_node_->IsMainFrame())) {
      navigation_handle_->set_net_error_code(net::ERR_ABORTED);
      frame_tree_node_->ResetNavigationRequest(false, true);
      return;
    }
  }

  if (navigation_data)
    navigation_handle_->set_navigation_data(std::move(navigation_data));

  navigation_handle_->set_proxy_server(response->head.proxy_server);

  common_params_.previews_state =
      GetContentClient()->browser()->DetermineCommittedPreviews(
          common_params_.previews_state, navigation_handle_.get(),
          response->head.headers.get());

  response_ = response;
  url_loader_client_endpoints_ = std::move(url_loader_client_endpoints);
  ssl_info_ = response->head.ssl_info;

  subresource_loader_params_ = std::move(subresource_loader_params);

  if (render_frame_host_ &&
      SiteInstanceImpl::ShouldAssignSiteForURL(common_params_.url)) {
    render_frame_host_->GetProcess()->SetIsUsed();

    SiteInstanceImpl* instance = render_frame_host_->GetSiteInstance();
    if (!instance->HasSite() &&
        SiteInstanceImpl::DoesSiteRequireDedicatedProcess(
            instance->GetBrowserContext(), instance->GetIsolationContext(),
            common_params_.url)) {
      instance->SetSite(common_params_.url);
    }
  }

  devtools_instrumentation::OnNavigationResponseReceived(*this, *response);

  if (is_download_ && (response->head.headers.get() &&
                       (response->head.headers->response_code() / 100 != 2))) {
    OnRequestFailedInternal(
        network::URLLoaderCompletionStatus(net::ERR_INVALID_RESPONSE),
        false /* skip_throttles */, base::nullopt /* error_page_content */,
        false /* collapse_frame */);

    return;
  }

  net::Error net_error = CheckContentSecurityPolicy(
      navigation_handle_->WasServerRedirect() /* has_followed_redirect */,
      false /* url_upgraded_after_redirect */, true /* is_response_check */);
  if (net_error != net::OK) {
    OnRequestFailedInternal(network::URLLoaderCompletionStatus(net_error),
                            false /* skip_throttles */,
                            base::nullopt /* error_page_content */,
                            false /* collapse_frame */);

    return;
  }

  navigation_handle_->WillProcessResponse(
      base::Bind(&NavigationRequest::OnWillProcessResponseChecksComplete,
                 base::Unretained(this)));
}
