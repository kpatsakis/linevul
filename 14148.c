void RenderFrameImpl::DidObserveLoadingBehavior(
    blink::WebLoadingBehaviorFlag behavior) {
  for (auto& observer : observers_)
    observer.DidObserveLoadingBehavior(behavior);
}
