void RenderWidgetHostImpl::ProcessGestureAck(bool processed, int type) {
  if (overscroll_controller_.get()) {
    overscroll_controller_->ReceivedEventACK(
        gesture_event_filter_->GetGestureEventAwaitingAck(), processed);
  }
  gesture_event_filter_->ProcessGestureAck(processed, type);
}
