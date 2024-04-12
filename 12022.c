bool RenderFrameHostImpl::CheckOrDispatchBeforeUnloadForSubtree(
    bool subframes_only,
    bool send_ipc,
    bool is_reload) {
  bool found_beforeunload = false;
  for (FrameTreeNode* node :
       frame_tree_node_->frame_tree()->SubtreeNodes(frame_tree_node_)) {
    RenderFrameHostImpl* rfh = node->current_frame_host();

    if (subframes_only && rfh->GetSiteInstance() == GetSiteInstance())
      continue;

    if (!rfh->IsRenderFrameLive())
      continue;

    bool should_run_beforeunload =
        rfh->GetSuddenTerminationDisablerState(blink::kBeforeUnloadHandler);
    if (rfh == this)
      should_run_beforeunload = true;

    if (!should_run_beforeunload)
      continue;

    found_beforeunload = true;
    if (!send_ipc)
      return true;


    while (!rfh->is_local_root() && rfh != this)
      rfh = rfh->GetParent();
    if (base::ContainsKey(beforeunload_pending_replies_, rfh))
      continue;

    bool has_same_site_ancestor = false;
    for (auto* added_rfh : beforeunload_pending_replies_) {
      if (rfh->IsDescendantOf(added_rfh) &&
          rfh->GetSiteInstance() == added_rfh->GetSiteInstance()) {
        has_same_site_ancestor = true;
        break;
      }
    }
    if (has_same_site_ancestor)
      continue;

    beforeunload_pending_replies_.insert(rfh);

    rfh->Send(new FrameMsg_BeforeUnload(rfh->GetRoutingID(), is_reload));
  }

  return found_beforeunload;
}
