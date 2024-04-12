bool RenderWidgetHostImpl::ScheduleComposite() {
  if (is_hidden_ || current_size_.IsEmpty() || repaint_ack_pending_ ||
      resize_ack_pending_) {
    return false;
  }

  repaint_start_time_ = TimeTicks::Now();
  repaint_ack_pending_ = true;
  TRACE_EVENT_ASYNC_BEGIN0(
      "renderer_host", "RenderWidgetHostImpl::repaint_ack_pending_", this);
  Send(new ViewMsg_Repaint(routing_id_, current_size_));
  return true;
}
