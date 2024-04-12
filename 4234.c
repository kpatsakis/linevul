base::WaitableEvent* RenderThreadImpl::GetShutDownEvent() {
  return ChildProcess::current()->GetShutDownEvent();
}
