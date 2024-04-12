void HistoryController::CreateNewBackForwardItem(
    RenderFrameImpl* target_frame,
    const WebHistoryItem& new_item,
    bool clone_children_of_target) {
  if (!current_entry_) {
    current_entry_.reset(new HistoryEntry(new_item));
  } else {
    current_entry_.reset(current_entry_->CloneAndReplace(
        new_item, clone_children_of_target, target_frame, render_view_));
  }
}
