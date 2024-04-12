bool RenderFrameHostImpl::DidCommitNavigationInternal(
    FrameHostMsg_DidCommitProvisionalLoad_Params* validated_params,
    bool is_same_document_navigation) {
  DCHECK_EQ(ui::PageTransitionIsMainFrame(validated_params->transition),
            !GetParent());

  UMACommitReport(validated_params->report_type,
                  validated_params->ui_timestamp);

  if (!ValidateDidCommitParams(validated_params))
    return false;

  if (!navigation_request_) {
    if (!is_loading()) {
      bool was_loading = frame_tree_node()->frame_tree()->IsLoading();
      is_loading_ = true;
      frame_tree_node()->DidStartLoading(true, was_loading);
    }
    pending_commit_ = false;
  }

  if (navigation_request_)
    was_discarded_ = navigation_request_->request_params().was_discarded;

  std::unique_ptr<NavigationHandleImpl> navigation_handle;

  if (is_same_document_navigation)
    navigation_handle =
        TakeNavigationHandleForSameDocumentCommit(*validated_params);
  else
    navigation_handle = TakeNavigationHandleForCommit(*validated_params);
  DCHECK(navigation_handle);

  UpdateSiteURL(validated_params->url, validated_params->url_is_unreachable);

  accessibility_reset_count_ = 0;
  frame_tree_node()->navigator()->DidNavigate(this, *validated_params,
                                              std::move(navigation_handle),
                                              is_same_document_navigation);

  return true;
}
