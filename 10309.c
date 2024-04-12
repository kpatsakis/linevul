void RenderFrameHostImpl::UpdateActiveSchedulerTrackedFeatures(
    uint64_t features_mask) {
  scheduler_tracked_features_ = features_mask;
}
