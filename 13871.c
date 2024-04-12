void RenderFrameHostManager::CommitPending() {
  TRACE_EVENT1("navigation", "RenderFrameHostManager::CommitPending",
               "FrameTreeNode id", frame_tree_node_->frame_tree_node_id());
  DCHECK(pending_render_frame_host_ || speculative_render_frame_host_);

  bool is_main_frame = frame_tree_node_->IsMainFrame();

  bool will_focus_location_bar =
      is_main_frame && delegate_->FocusLocationBarByDefault();

  bool focus_render_view = !will_focus_location_bar &&
                           render_frame_host_->GetView() &&
                           render_frame_host_->GetView()->HasFocus();

  frame_tree_node_->ResetForNewProcess();

  std::unique_ptr<RenderFrameHostImpl> old_render_frame_host;
  if (!IsBrowserSideNavigationEnabled()) {
    DCHECK(!speculative_render_frame_host_);
    old_render_frame_host =
        SetRenderFrameHost(std::move(pending_render_frame_host_));
  } else {
    DCHECK(speculative_render_frame_host_);
    old_render_frame_host =
        SetRenderFrameHost(std::move(speculative_render_frame_host_));
  }

  SkColor old_background_color = SK_ColorWHITE;
  bool has_old_background_color = false;
  if (old_render_frame_host->GetView()) {
    has_old_background_color = true;
    old_background_color = old_render_frame_host->GetView()->background_color();
  }

  bool new_rfh_has_view = !!render_frame_host_->GetView();
  if (!delegate_->IsHidden() && new_rfh_has_view) {
    render_frame_host_->GetView()->Show();
  }
  render_frame_host_->GetProcess()->RemovePendingView();

  if (!new_rfh_has_view) {
    DCHECK(!render_frame_host_->IsRenderFrameLive());
    DCHECK(!render_frame_host_->render_view_host()->IsRenderViewLive());
    render_frame_host_->ResetLoadingState();
    delegate_->RenderProcessGoneFromRenderManager(
        render_frame_host_->render_view_host());
  }

  if (is_main_frame &&
      old_render_frame_host->render_view_host()->GetWidget()->GetView()) {
    old_render_frame_host->render_view_host()->GetWidget()->GetView()->Hide();
  }

  delegate_->UpdateRenderViewSizeForRenderManager();

  if (will_focus_location_bar) {
    delegate_->SetFocusToLocationBar(false);
  } else if (focus_render_view && render_frame_host_->GetView()) {
    if (is_main_frame) {
      render_frame_host_->GetView()->Focus();
    } else {
      frame_tree_node_->frame_tree()->SetPageFocus(
          render_frame_host_->GetSiteInstance(), true);
    }
  }

  delegate_->NotifySwappedFromRenderManager(
      old_render_frame_host.get(), render_frame_host_.get(), is_main_frame);

  if (has_old_background_color && render_frame_host_->GetView())
    render_frame_host_->GetView()->SetBackgroundColor(old_background_color);

  if (is_main_frame) {
    RenderViewHostImpl* rvh = render_frame_host_->render_view_host();
    rvh->set_main_frame_routing_id(render_frame_host_->routing_id());

    if (!rvh->is_active())
      rvh->PostRenderViewReady();

    rvh->set_is_active(true);
    rvh->set_is_swapped_out(false);
    old_render_frame_host->render_view_host()->set_main_frame_routing_id(
        MSG_ROUTING_NONE);
  }

  SwapOutOldFrame(std::move(old_render_frame_host));

  DeleteRenderFrameProxyHost(render_frame_host_->GetSiteInstance());

  RenderFrameProxyHost* proxy_to_parent = GetProxyToParent();
  if (proxy_to_parent) {
    CHECK(SiteIsolationPolicy::AreCrossProcessFramesPossible());
    proxy_to_parent->SetChildRWHView(render_frame_host_->GetView());
  }

  CHECK(!GetRenderFrameProxyHost(render_frame_host_->GetSiteInstance()));
}
