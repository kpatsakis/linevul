void RenderFrameImpl::DidStartProvisionalLoad(
    blink::WebDocumentLoader* document_loader,
    blink::WebURLRequest& request) {
  if (!document_loader)
    return;

  TRACE_EVENT2("navigation,benchmark,rail",
               "RenderFrameImpl::didStartProvisionalLoad", "id", routing_id_,
               "url", document_loader->GetRequest().Url().GetString().Utf8());

  if (pending_navigation_info_.get()) {
    NavigationPolicyInfo info(request);
    info.navigation_type = pending_navigation_info_->navigation_type;
    info.default_policy = pending_navigation_info_->policy;
    info.replaces_current_history_item =
        pending_navigation_info_->replaces_current_history_item;
    info.is_history_navigation_in_new_child_frame =
        pending_navigation_info_->history_navigation_in_new_child_frame;
    info.is_client_redirect = pending_navigation_info_->client_redirect;
    info.triggering_event_info =
        pending_navigation_info_->triggering_event_info;
    info.form = pending_navigation_info_->form;
    info.source_location = pending_navigation_info_->source_location;

    pending_navigation_info_.reset(nullptr);
    BeginNavigation(info);
  }

  DocumentState* document_state =
      DocumentState::FromDocumentLoader(document_loader);
  NavigationStateImpl* navigation_state = static_cast<NavigationStateImpl*>(
      document_state->navigation_state());
  bool is_top_most = !frame_->Parent();
  if (is_top_most) {
    auto navigation_gesture =
        WebUserGestureIndicator::IsProcessingUserGesture(frame_)
            ? NavigationGestureUser
            : NavigationGestureAuto;
    render_view_->set_navigation_gesture(navigation_gesture);
  } else if (document_loader->ReplacesCurrentHistoryItem()) {
    navigation_state->set_transition_type(ui::PAGE_TRANSITION_AUTO_SUBFRAME);
  }

  base::TimeTicks navigation_start =
      navigation_state->common_params().navigation_start;
  DCHECK(!navigation_start.is_null());

  {
    SCOPED_UMA_HISTOGRAM_TIMER("RenderFrameObservers.DidStartProvisionalLoad");
    for (auto& observer : observers_)
      observer.DidStartProvisionalLoad(document_loader);
  }

  std::vector<GURL> redirect_chain;
  GetRedirectChain(document_loader, &redirect_chain);

  if (ConsumeGestureOnNavigation())
    WebUserGestureIndicator::ConsumeUserGesture(frame_);

  Send(new FrameHostMsg_DidStartProvisionalLoad(
      routing_id_, document_loader->GetRequest().Url(), redirect_chain,
      navigation_start));
}
