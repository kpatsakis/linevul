bool RenderProcessHostImpl::FastShutdownIfPossible() {
  if (run_renderer_in_process())
    return false;  // Single process mode never shutdown the renderer.

  if (!GetContentClient()->browser()->IsFastShutdownPossible())
    return false;

  if (!child_process_launcher_.get() ||
      child_process_launcher_->IsStarting() ||
      !GetHandle())
    return false;  // Render process hasn't started or is probably crashed.

  if (!SuddenTerminationAllowed())
    return false;

  ProcessDied(false /* already_dead */);
  fast_shutdown_started_ = true;
  return true;
}
