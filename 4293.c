void WebContentsImpl::OnUserInteraction(const blink::WebInputEvent::Type type) {
  FOR_EACH_OBSERVER(WebContentsObserver, observers_,
                    DidGetUserInteraction(type));
}
