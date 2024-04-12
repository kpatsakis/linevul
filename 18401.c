void DevToolsSession::InspectElement(const gfx::Point& point) {
  if (session_ptr_)
    session_ptr_->InspectElement(point);
}
