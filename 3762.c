bool ClientSession::ShouldIgnoreRemoteMouseInput(
    const protocol::MouseEvent& event) const {
  if (remote_mouse_button_state_ != 0)
    return false;
  if (awaiting_continue_approval_)
    return true;
  int64 millis = (base::Time::Now() - latest_local_input_time_)
                 .InMilliseconds();
  if (millis < kRemoteBlockTimeoutMillis)
    return true;
  return false;
}
