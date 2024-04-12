bool RunLoop::IsRunningOnCurrentThread() {
  Delegate* delegate = tls_delegate.Get().Get();
  return delegate && !delegate->active_run_loops_.empty();
}
