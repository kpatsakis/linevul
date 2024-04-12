void RenderFrameHostImpl::UpdateFrameFrozenState() {
  if (!base::FeatureList::IsEnabled(features::kFreezeFramesOnVisibility))
    return;

  if (is_loading_)
    return;

  if (visibility_ == blink::mojom::FrameVisibility::kNotRendered) {
    frame_->SetLifecycleState(blink::mojom::FrameLifecycleState::kFrozen);
  } else if (visibility_ ==
             blink::mojom::FrameVisibility::kRenderedOutOfViewport) {
    frame_->SetLifecycleState(
        blink::mojom::FrameLifecycleState::kFrozenAutoResumeMedia);
  } else {
    frame_->SetLifecycleState(blink::mojom::FrameLifecycleState::kRunning);
  }
}
