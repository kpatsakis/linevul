void LayerTreeHostImpl::PinchGestureUpdate(float magnify_delta,
                                           const gfx::Point& anchor) {
  TRACE_EVENT0("cc", "LayerTreeHostImpl::PinchGestureUpdate");
  if (!InnerViewportScrollLayer())
    return;
  viewport()->PinchUpdate(magnify_delta, anchor);
  client_->SetNeedsCommitOnImplThread();
  SetNeedsRedraw();
  client_->RenewTreePriority();
  UpdateRootLayerStateForSynchronousInputHandler();
}
