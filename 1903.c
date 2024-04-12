void WebGLRenderingContextBase::DispatchContextLostEvent(TimerBase*) {
  WebGLContextEvent* event = WebGLContextEvent::Create(
      EventTypeNames::webglcontextlost, false, true, "");
  Host()->HostDispatchEvent(event);
  restore_allowed_ = event->defaultPrevented();
  if (restore_allowed_ && !is_hidden_) {
    if (auto_recovery_method_ == kAuto)
      restore_timer_.StartOneShot(TimeDelta(), FROM_HERE);
  }
}
