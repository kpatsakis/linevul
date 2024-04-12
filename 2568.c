RenderFrameHostImpl::TakeNavigationRequestForSameDocumentCommit(
    const FrameHostMsg_DidCommitProvisionalLoad_Params& params) {
  bool is_browser_initiated = (params.nav_entry_id != 0);

  if (is_browser_initiated && same_document_navigation_request_ &&
      same_document_navigation_request_->common_params().url == params.url) {
    return std::move(same_document_navigation_request_);
  }

  bool is_renderer_initiated = true;
  int pending_nav_entry_id = 0;
  NavigationEntryImpl* pending_entry = NavigationEntryImpl::FromNavigationEntry(
      frame_tree_node()->navigator()->GetController()->GetPendingEntry());
  if (pending_entry && pending_entry->GetUniqueID() == params.nav_entry_id) {
    pending_nav_entry_id = params.nav_entry_id;
    is_renderer_initiated = pending_entry->is_renderer_initiated();
  }

  return NavigationRequest::CreateForCommit(
      frame_tree_node_, pending_entry, params, is_renderer_initiated,
      true /* was_within_same_document */);
}
