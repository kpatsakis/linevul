WebNavigationPolicy RenderFrameImpl::DecidePolicyForNavigation(
    const NavigationPolicyInfo& info) {
  bool is_content_initiated =
      info.extra_data ? static_cast<DocumentState*>(info.extra_data)
                            ->navigation_state()
                            ->IsContentInitiated()
                      : !IsBrowserInitiated(pending_navigation_params_.get());

  const GURL& url = info.url_request.Url();

  bool is_redirect =
      info.extra_data ||
      (pending_navigation_params_ &&
       !pending_navigation_params_->request_params.redirects.empty() &&
       url != pending_navigation_params_->request_params.redirects[0]);

#ifdef OS_ANDROID
  bool render_view_was_created_by_renderer =
      render_view_->was_created_by_renderer_;
  if (!IsURLHandledByNetworkStack(url) &&
      GetContentClient()->renderer()->HandleNavigation(
          this, is_content_initiated, render_view_was_created_by_renderer,
          frame_, info.url_request, info.navigation_type, info.default_policy,
          is_redirect)) {
    return blink::kWebNavigationPolicyIgnore;
  }
#endif

  if (is_content_initiated && IsTopLevelNavigation(frame_) &&
      render_view_->renderer_preferences_
          .browser_handles_all_top_level_requests) {
    OpenURL(info, /*send_referrer=*/true,
            /*is_history_navigation_in_new_child=*/false);
    return blink::kWebNavigationPolicyIgnore;  // Suppress the load here.
  }

  if (info.is_history_navigation_in_new_child_frame && is_content_initiated &&
      frame_->Parent()) {
    bool should_ask_browser = false;
    RenderFrameImpl* parent = RenderFrameImpl::FromWebFrame(frame_->Parent());
    auto iter = parent->history_subframe_unique_names_.find(
        unique_name_helper_.value());
    if (iter != parent->history_subframe_unique_names_.end()) {
      bool history_item_is_about_blank = iter->second;
      should_ask_browser =
          !history_item_is_about_blank || url != url::kAboutBlankURL;
      parent->history_subframe_unique_names_.erase(iter);
    }

    if (should_ask_browser) {
      if (!info.is_client_redirect) {
        OpenURL(info, /*send_referrer=*/true,
                /*is_history_navigation_in_new_child=*/true);
        return blink::kWebNavigationPolicyHandledByClientForInitialHistory;
      } else {
        GetFrameHost()->CancelInitialHistoryLoad();
      }
    }
  }

  GURL old_url(frame_->GetDocumentLoader()->GetRequest().Url());

  if (!frame_->Parent() && is_content_initiated &&
      !url.SchemeIs(url::kAboutScheme)) {
    bool send_referrer = false;

    int cumulative_bindings = RenderProcess::current()->GetEnabledBindings();
    bool is_initial_navigation = render_view_->history_list_length_ == 0;
    bool should_fork =
        HasWebUIScheme(url) || HasWebUIScheme(old_url) ||
        (cumulative_bindings & BINDINGS_POLICY_WEB_UI) ||
        url.SchemeIs(kViewSourceScheme) ||
        (frame_->IsViewSourceModeEnabled() &&
         info.navigation_type != blink::kWebNavigationTypeReload);

    if (!should_fork && url.SchemeIs(url::kFileScheme)) {
      should_fork = !old_url.SchemeIs(url::kFileScheme);
    }

    if (!should_fork) {
      should_fork = GetContentClient()->renderer()->ShouldFork(
          frame_, url, info.url_request.HttpMethod().Utf8(),
          is_initial_navigation, is_redirect, &send_referrer);
    }

    if (should_fork) {
      OpenURL(info, send_referrer,
              /*is_history_navigation_in_new_child=*/false);
      return blink::kWebNavigationPolicyIgnore;  // Suppress the load here.
    }
  }

  bool is_fork =
      old_url == url::kAboutBlankURL &&
      render_view_->HistoryBackListCount() < 1 &&
      render_view_->HistoryForwardListCount() < 1 &&
      frame_->Opener() == nullptr &&
      frame_->Parent() == nullptr &&
      is_content_initiated &&
      info.default_policy == blink::kWebNavigationPolicyCurrentTab &&
      info.navigation_type == blink::kWebNavigationTypeOther;

  if (is_fork) {
    OpenURL(info, /*send_referrer=*/false,
            /*is_history_navigation_in_new_child=*/false);
    return blink::kWebNavigationPolicyIgnore;
  }

  bool should_dispatch_before_unload =
      info.default_policy == blink::kWebNavigationPolicyCurrentTab &&
      !is_redirect &&
      info.url_request.CheckForBrowserSideNavigation() &&
      (has_accessed_initial_document_ || !current_history_item_.IsNull());

  if (should_dispatch_before_unload) {
    base::WeakPtr<RenderFrameImpl> weak_self = weak_factory_.GetWeakPtr();

    if (!frame_->DispatchBeforeUnloadEvent(info.navigation_type ==
                                           blink::kWebNavigationTypeReload) ||
        !weak_self) {
      return blink::kWebNavigationPolicyIgnore;
    }

    if (pending_navigation_params_) {
      pending_navigation_params_->common_params.navigation_start =
          base::TimeTicks::Now();
    }
  }

  bool use_archive =
      (info.archive_status == NavigationPolicyInfo::ArchiveStatus::Present) &&
      !url.SchemeIs(url::kDataScheme);

  if (info.url_request.CheckForBrowserSideNavigation() &&
      IsURLHandledByNetworkStack(url) && !use_archive) {
    if (info.default_policy == blink::kWebNavigationPolicyCurrentTab) {
      pending_navigation_info_.reset(new PendingNavigationInfo(info));
      return blink::kWebNavigationPolicyHandledByClient;
    } else if (info.default_policy == blink::kWebNavigationPolicyDownload) {
      DownloadURL(info.url_request, blink::WebString());
      return blink::kWebNavigationPolicyIgnore;
    } else {
      OpenURL(info, /*send_referrer=*/true,
              /*is_history_navigation_in_new_child=*/false);
      return blink::kWebNavigationPolicyIgnore;
    }
  }

  if (info.default_policy == blink::kWebNavigationPolicyCurrentTab ||
      info.default_policy == blink::kWebNavigationPolicyDownload) {
    return info.default_policy;
  }
  OpenURL(info, /*send_referrer=*/true,
          /*is_history_navigation_in_new_child=*/false);
  return blink::kWebNavigationPolicyIgnore;
}
