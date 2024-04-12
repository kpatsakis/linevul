void RenderWidgetHostImpl::RendererExited(base::TerminationStatus status,
                                          int exit_code) {
  if (!renderer_initialized_)
    return;

  monitoring_composition_info_ = false;

  renderer_initialized_ = false;

  waiting_for_screen_rects_ack_ = false;

  suppress_events_until_keydown_ = false;

  ResetSentVisualProperties();
  if (!is_hidden_) {
    is_hidden_ = true;
    if (!destroyed_)
      process_->UpdateClientPriority(this);
  }

  in_flight_event_count_ = 0;
  StopInputEventAckTimeout();

  if (view_) {
    view_->RenderProcessGone(status, exit_code);
    view_.reset();  // The View should be deleted by RenderProcessGone.
  }

  SetupInputRouter();
  synthetic_gesture_controller_.reset();

  current_content_source_id_ = 0;

  frame_token_message_queue_->Reset();
}
