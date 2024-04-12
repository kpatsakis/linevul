void RenderFrameHostImpl::DispatchBeforeUnload(BeforeUnloadType type,
                                               bool is_reload) {
  bool for_navigation =
      type == BeforeUnloadType::BROWSER_INITIATED_NAVIGATION ||
      type == BeforeUnloadType::RENDERER_INITIATED_NAVIGATION;
  bool for_inner_delegate_attach =
      type == BeforeUnloadType::INNER_DELEGATE_ATTACH;
  DCHECK(for_navigation || for_inner_delegate_attach || !is_reload);

  DCHECK(type == BeforeUnloadType::BROWSER_INITIATED_NAVIGATION ||
         type == BeforeUnloadType::RENDERER_INITIATED_NAVIGATION ||
         type == BeforeUnloadType::INNER_DELEGATE_ATTACH ||
         frame_tree_node_->IsMainFrame());

  if (!for_navigation) {
    if (frame_tree_node_->navigation_request() &&
        frame_tree_node_->navigation_request()->navigation_handle()) {
      frame_tree_node_->navigation_request()
          ->navigation_handle()
          ->set_net_error_code(net::ERR_ABORTED);
    }
    frame_tree_node_->ResetNavigationRequest(false, true);
  }

  bool check_subframes_only =
      type == BeforeUnloadType::RENDERER_INITIATED_NAVIGATION;
  if (!ShouldDispatchBeforeUnload(check_subframes_only)) {
    DCHECK(!for_navigation);

    base::OnceClosure task = base::BindOnce(
        [](base::WeakPtr<RenderFrameHostImpl> self) {
          if (!self)
            return;
          self->frame_tree_node_->render_manager()->OnBeforeUnloadACK(
              true, base::TimeTicks::Now());
        },
        weak_ptr_factory_.GetWeakPtr());
    base::ThreadTaskRunnerHandle::Get()->PostTask(FROM_HERE, std::move(task));
    return;
  }
  TRACE_EVENT_ASYNC_BEGIN1("navigation", "RenderFrameHostImpl BeforeUnload",
                           this, "&RenderFrameHostImpl", (void*)this);

  if (is_waiting_for_beforeunload_ack_) {
    unload_ack_is_for_navigation_ =
        unload_ack_is_for_navigation_ && for_navigation;
  } else {
    is_waiting_for_beforeunload_ack_ = true;
    beforeunload_dialog_request_cancels_unload_ = false;
    unload_ack_is_for_navigation_ = for_navigation;
    send_before_unload_start_time_ = base::TimeTicks::Now();
    if (render_view_host_->GetDelegate()->IsJavaScriptDialogShowing()) {
      SimulateBeforeUnloadAck(type != BeforeUnloadType::DISCARD);
    } else {
      if (beforeunload_timeout_)
        beforeunload_timeout_->Start(beforeunload_timeout_delay_);

      beforeunload_pending_replies_.clear();
      beforeunload_dialog_request_cancels_unload_ =
          (type == BeforeUnloadType::DISCARD);

      CheckOrDispatchBeforeUnloadForSubtree(check_subframes_only,
                                            true /* send_ipc */, is_reload);
    }
  }
}
