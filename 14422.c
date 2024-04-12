void RenderFrameImpl::UpdateStateForCommit(
    const blink::WebHistoryItem& item,
    blink::WebHistoryCommitType commit_type,
    ui::PageTransition transition) {
  InternalDocumentStateData* internal_data =
      InternalDocumentStateData::FromDocumentLoader(
          frame_->GetDocumentLoader());
  NavigationState* navigation_state = internal_data->navigation_state();

  SendUpdateState();

  bool is_new_navigation = UpdateNavigationHistory(item, commit_type);
  NotifyObserversOfNavigationCommit(
      is_new_navigation, navigation_state->WasWithinSameDocument(), transition);

  if (internal_data->must_reset_scroll_and_scale_state()) {
    render_view_->webview()->ResetScrollAndScaleState();
    internal_data->set_must_reset_scroll_and_scale_state(false);
  }
  UpdateZoomLevel();

  if (!frame_->Parent()) {  // Only for top frames.
    RenderThreadImpl* render_thread_impl = RenderThreadImpl::current();
    if (render_thread_impl) {  // Can be NULL in tests.
      render_thread_impl->histogram_customizer()->RenderViewNavigatedToHost(
          GURL(GetLoadingUrl()).host(), RenderView::GetRenderViewCount());
    }
  }

  navigation_state->set_request_committed(true);

  if (!frame_->Parent() && !navigation_state->WasWithinSameDocument()) {
    render_view_->webview()->ClearAutoplayFlags();
  }

  if (url::Origin(frame_->GetSecurityOrigin()) == autoplay_flags_.first) {
    render_view_->webview()->AddAutoplayFlags(autoplay_flags_.second);
    autoplay_flags_.first = url::Origin();
  }
}
