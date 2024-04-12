void RenderFrameHostImpl::DidCommitProvisionalLoad(
    std::unique_ptr<FrameHostMsg_DidCommitProvisionalLoad_Params>
        validated_params,
    service_manager::mojom::InterfaceProviderRequest
        interface_provider_request) {
  if (GetNavigationHandle()) {
    main_frame_request_ids_ = {validated_params->request_id,
                               GetNavigationHandle()->GetGlobalRequestID()};
    if (deferred_main_frame_load_info_)
      ResourceLoadComplete(std::move(deferred_main_frame_load_info_));
  }
  ScopedActiveURL scoped_active_url(
      validated_params->url,
      frame_tree_node()->frame_tree()->root()->current_origin());

  ScopedCommitStateResetter commit_state_resetter(this);
  RenderProcessHost* process = GetProcess();

  TRACE_EVENT2("navigation", "RenderFrameHostImpl::DidCommitProvisionalLoad",
               "url", validated_params->url.possibly_invalid_spec(), "details",
               CommitAsTracedValue(validated_params.get()));

  NotifyResourceSchedulerOfNavigation(process->GetID(), *validated_params);

  if (is_waiting_for_beforeunload_ack_ && unload_ack_is_for_navigation_ &&
      !GetParent()) {
    base::TimeTicks approx_renderer_start_time = send_before_unload_start_time_;
    ProcessBeforeUnloadACK(true /* proceed */, true /* treat_as_final_ack */,
                           approx_renderer_start_time, base::TimeTicks::Now());
  }

  if (is_waiting_for_swapout_ack_)
    return;

  DCHECK(document_scoped_interface_provider_binding_.is_bound());

  if (interface_provider_request.is_pending()) {
    auto interface_provider_request_of_previous_document =
        document_scoped_interface_provider_binding_.Unbind();
    dropped_interface_request_logger_ =
        std::make_unique<DroppedInterfaceRequestLogger>(
            std::move(interface_provider_request_of_previous_document));
    BindInterfaceProviderRequest(std::move(interface_provider_request));
  } else {
    if (frame_tree_node_->has_committed_real_load()) {
      document_scoped_interface_provider_binding_.Close();
      bad_message::ReceivedBadMessage(
          process, bad_message::RFH_INTERFACE_PROVIDER_MISSING);
      return;
    }

  }

  if (!DidCommitNavigationInternal(validated_params.get(),
                                   false /* is_same_document_navigation */))
    return;

  commit_state_resetter.disable();

  if (frame_tree_node_->IsMainFrame() && GetView()) {
    RenderWidgetHostImpl::From(GetView()->GetRenderWidgetHost())
        ->DidNavigate(validated_params->content_source_id);
  }
}
