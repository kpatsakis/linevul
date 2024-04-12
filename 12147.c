void RenderFrameHostManager::ClearWebUIInstances() {
  current_frame_host()->ClearAllWebUI();
  if (speculative_render_frame_host_)
    speculative_render_frame_host_->ClearAllWebUI();
}
