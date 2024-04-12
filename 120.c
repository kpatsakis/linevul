TargetHandler::Throttle::WillProcessResponse() {
  if (!target_handler_)
    return PROCEED;
  agent_host_ =
      target_handler_->auto_attacher_.AutoAttachToFrame(navigation_handle());
  if (!agent_host_.get())
    return PROCEED;
  target_handler_->auto_attached_sessions_[agent_host_.get()]->SetThrottle(
      this);
  return DEFER;
}
