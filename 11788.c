void RenderFrameHostImpl::SwapOut(
    RenderFrameProxyHost* proxy,
    bool is_loading) {
  TRACE_EVENT_ASYNC_BEGIN1("navigation", "RenderFrameHostImpl::SwapOut", this,
                           "frame_tree_node",
                           frame_tree_node_->frame_tree_node_id());

  if (unload_state_ != UnloadState::NotRun) {
    NOTREACHED() << "RFH should be in default state when calling SwapOut.";
    return;
  }

  if (swapout_event_monitor_timeout_) {
    swapout_event_monitor_timeout_->Start(base::TimeDelta::FromMilliseconds(
        RenderViewHostImpl::kUnloadTimeoutMS));
  }

  CHECK(proxy);

  is_waiting_for_swapout_ack_ = true;
  unload_state_ = UnloadState::InProgress;

  if (IsRenderFrameLive()) {
    FrameReplicationState replication_state =
        proxy->frame_tree_node()->current_replication_state();
    Send(new FrameMsg_SwapOut(routing_id_, proxy->GetRoutingID(), is_loading,
                              replication_state));
    proxy->set_render_frame_proxy_created(true);

    StartPendingDeletionOnSubtree();
  }

  PendingDeletionCheckCompletedOnSubtree();

  if (web_ui())
    web_ui()->RenderFrameHostSwappingOut();

  web_bluetooth_services_.clear();
}
