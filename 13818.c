void WebContentsImpl::OnUserInteraction(
    RenderWidgetHostImpl* render_widget_host,
    const blink::WebInputEvent::Type type) {
  if (!HasMatchingWidgetHost(&frame_tree_, render_widget_host))
    return;

  for (auto& observer : observers_)
    observer.DidGetUserInteraction(type);

  ResourceDispatcherHostImpl* rdh = ResourceDispatcherHostImpl::Get();
  if (rdh && type != blink::WebInputEvent::kMouseWheel)
    rdh->OnUserGesture();
}
