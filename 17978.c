void RenderFrameHostImpl::AllowBindings(int bindings_flags) {
  if (GetProcess()->IsForGuestsOnly()) {
    NOTREACHED() << "Never grant bindings to a guest process.";
    return;
  }
  TRACE_EVENT2("navigation", "RenderFrameHostImpl::AllowBindings",
               "frame_tree_node", frame_tree_node_->frame_tree_node_id(),
               "bindings flags", bindings_flags);

  int webui_bindings = bindings_flags & kWebUIBindingsPolicyMask;

  if (webui_bindings && GetProcess()->IsInitializedAndNotDead() &&
      !ChildProcessSecurityPolicyImpl::GetInstance()->HasWebUIBindings(
          GetProcess()->GetID())) {
    if (GetProcess()->GetActiveViewCount() > 1 &&
        !base::CommandLine::ForCurrentProcess()->HasSwitch(
            switches::kSingleProcess))
      return;
  }

  if (webui_bindings) {
    ChildProcessSecurityPolicyImpl::GetInstance()->GrantWebUIBindings(
        GetProcess()->GetID(), webui_bindings);
  }

  enabled_bindings_ |= bindings_flags;
  if (GetParent())
    DCHECK_EQ(GetParent()->GetEnabledBindings(), GetEnabledBindings());

  if (render_frame_created_) {
    if (!frame_bindings_control_)
      GetRemoteAssociatedInterfaces()->GetInterface(&frame_bindings_control_);
    frame_bindings_control_->AllowBindings(enabled_bindings_);
  }
}
