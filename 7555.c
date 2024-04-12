void RenderFrameHostImpl::DetachFromProxy() {
  if (unload_state_ != UnloadState::NotRun)
    return;

  DeleteRenderFrame();
  StartPendingDeletionOnSubtree();
  PendingDeletionCheckCompletedOnSubtree();
}
