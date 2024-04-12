void RenderViewImpl::OnSetHistoryLengthAndPrune(int history_length,
                                                int32 minimum_page_id) {
  DCHECK(history_length >= 0);
  DCHECK(history_list_offset_ == history_list_length_ - 1);
  DCHECK(minimum_page_id >= -1);

  std::vector<int32> new_history_page_ids(history_length, -1);
  for (size_t i = 0; i < history_page_ids_.size(); ++i) {
    if (minimum_page_id >= 0 && history_page_ids_[i] < minimum_page_id)
      continue;
    new_history_page_ids.push_back(history_page_ids_[i]);
  }
  new_history_page_ids.swap(history_page_ids_);

  history_list_length_ = history_page_ids_.size();
  history_list_offset_ = history_list_length_ - 1;
}
