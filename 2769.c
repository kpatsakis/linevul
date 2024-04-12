bool RenderViewImpl::IsBackForwardToStaleEntry(
    const ViewMsg_Navigate_Params& params,
    bool is_reload) {
  bool is_back_forward = !is_reload && !params.state.empty();

  if (!is_back_forward || history_list_length_ <= 0)
    return false;

  DCHECK_EQ(static_cast<int>(history_page_ids_.size()), history_list_length_);

  if (params.pending_history_list_offset >= history_list_length_)
    return true;

  int expected_page_id =
      history_page_ids_[params.pending_history_list_offset];
  if (expected_page_id > 0 && params.page_id != expected_page_id) {
    if (params.page_id < expected_page_id)
      return true;

    history_page_ids_[params.pending_history_list_offset] = params.page_id;
  }

  return false;
}
