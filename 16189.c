bool RenderFrameImpl::UpdateNavigationHistory(
    const blink::WebHistoryItem& item,
    blink::WebHistoryCommitType commit_type) {
  NavigationState* navigation_state =
      NavigationState::FromDocumentLoader(frame_->GetDocumentLoader());
  const RequestNavigationParams& request_params =
      navigation_state->request_params();

  current_history_item_ = item;
  current_history_item_.SetTarget(
      blink::WebString::FromUTF8(unique_name_helper_.value()));
  bool is_new_navigation = commit_type == blink::kWebStandardCommit;
  if (request_params.should_clear_history_list) {
    render_view_->history_list_offset_ = 0;
    render_view_->history_list_length_ = 1;
  } else if (is_new_navigation) {
    DCHECK(!navigation_state->common_params().should_replace_current_entry ||
           render_view_->history_list_length_ > 0);
    if (!navigation_state->common_params().should_replace_current_entry) {
      render_view_->history_list_offset_++;
      if (render_view_->history_list_offset_ >= kMaxSessionHistoryEntries)
        render_view_->history_list_offset_ = kMaxSessionHistoryEntries - 1;
      render_view_->history_list_length_ =
          render_view_->history_list_offset_ + 1;
    }
  } else if (request_params.nav_entry_id != 0 &&
             !request_params.intended_as_new_entry) {
    render_view_->history_list_offset_ =
        navigation_state->request_params().pending_history_list_offset;
  }

  if (commit_type == blink::WebHistoryCommitType::kWebBackForwardCommit)
    render_view_->DidCommitProvisionalHistoryLoad();

  return is_new_navigation;
}
