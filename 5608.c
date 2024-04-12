RenderProcessHost::Priority RenderWidgetHostImpl::GetPriority() {
  RenderProcessHost::Priority priority = {
    is_hidden_,
    frame_depth_,
    intersects_viewport_,
#if defined(OS_ANDROID)
    importance_,
#endif
  };
  if (owner_delegate_ &&
      !owner_delegate_->ShouldContributePriorityToProcess()) {
    priority.is_hidden = true;
    priority.frame_depth = RenderProcessHostImpl::kMaxFrameDepthForPriority;
#if defined(OS_ANDROID)
    priority.importance = ChildProcessImportance::NORMAL;
#endif
  }
  return priority;
}
