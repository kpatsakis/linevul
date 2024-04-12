void RenderFrameImpl::BubbleLogicalScrollInParentFrame(
    blink::WebScrollDirection direction,
    blink::WebScrollGranularity granularity) {
  DCHECK(IsLocalRoot());
  DCHECK(!IsMainFrame());
  Send(new FrameHostMsg_BubbleLogicalScrollInParentFrame(routing_id_, direction,
                                                         granularity));
}
