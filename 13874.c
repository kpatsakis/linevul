void RenderFrameHostImpl::OnContextMenu(const ContextMenuParams& params) {
  if (!is_active())
    return;

  ContextMenuParams validated_params(params);
  RenderProcessHost* process = GetProcess();

  process->FilterURL(true, &validated_params.link_url);
  process->FilterURL(true, &validated_params.src_url);
  process->FilterURL(false, &validated_params.page_url);
  process->FilterURL(true, &validated_params.frame_url);

  gfx::Point original_point(validated_params.x, validated_params.y);
  gfx::Point transformed_point =
      static_cast<RenderWidgetHostViewBase*>(GetView())
          ->TransformPointToRootCoordSpace(original_point);
  validated_params.x = transformed_point.x();
  validated_params.y = transformed_point.y();

  if (validated_params.selection_start_offset < 0) {
    bad_message::ReceivedBadMessage(
        GetProcess(), bad_message::RFH_NEGATIVE_SELECTION_START_OFFSET);
  }

  delegate_->ShowContextMenu(this, validated_params);
}
