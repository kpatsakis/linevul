void RenderViewHostImpl::OnSwapOutACK(bool timed_out) {
  decrement_in_flight_event_count();
  StopHangMonitorTimeout();
  is_waiting_for_unload_ack_ = false;
  has_timed_out_on_unload_ = timed_out;
  delegate_->SwappedOut(this);
}
