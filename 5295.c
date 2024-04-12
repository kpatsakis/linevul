void RenderFrameHostImpl::AccessibilityPerformAction(
    const ui::AXActionData& action_data) {
  Send(new AccessibilityMsg_PerformAction(routing_id_, action_data));
}
