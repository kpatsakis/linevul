void NavigationRequest::CommitErrorPage(
    RenderFrameHostImpl* render_frame_host,
    const base::Optional<std::string>& error_page_content) {
  UpdateRequestNavigationParamsHistory();
  frame_tree_node_->TransferNavigationRequestOwnership(render_frame_host);
  if (IsPerNavigationMojoInterfaceEnabled() && request_navigation_client_ &&
      request_navigation_client_.is_bound()) {
    IgnorePipeDisconnection();
    if (associated_site_instance_id_ ==
        render_frame_host->GetSiteInstance()->GetId()) {
      commit_navigation_client_ = std::move(request_navigation_client_);
    }
    associated_site_instance_id_.reset();
  }

  navigation_handle_->ReadyToCommitNavigation(render_frame_host, true);
  render_frame_host->FailedNavigation(
      navigation_handle_->GetNavigationId(), common_params_, request_params_,
      has_stale_copy_in_cache_, net_error_, error_page_content);
}
