void RenderFrameHostImpl::DidCommitSameDocumentNavigation(
    std::unique_ptr<FrameHostMsg_DidCommitProvisionalLoad_Params>
        validated_params) {
  ScopedActiveURL scoped_active_url(
      validated_params->url,
      frame_tree_node()->frame_tree()->root()->current_origin());
  ScopedCommitStateResetter commit_state_resetter(this);

  if (!is_active())
    return;

  TRACE_EVENT2("navigation",
               "RenderFrameHostImpl::DidCommitSameDocumentNavigation",
               "frame_tree_node", frame_tree_node_->frame_tree_node_id(), "url",
               validated_params->url.possibly_invalid_spec());
  bool is_browser_initiated = (validated_params->nav_entry_id != 0);
  if (!DidCommitNavigationInternal(
          is_browser_initiated ? std::move(same_document_navigation_request_)
                               : nullptr,
          validated_params.get(), true /* is_same_document_navigation*/)) {
    return;
  }

  commit_state_resetter.disable();
}
