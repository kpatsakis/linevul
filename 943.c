void RenderFrameHostImpl::ResumeBlockedRequestsForFrame() {
  NotifyForEachFrameFromUI(
      this, base::BindRepeating(
                &ResourceDispatcherHostImpl::ResumeBlockedRequestsForRoute));
}
