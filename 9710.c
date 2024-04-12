void FrameSelection::SetCaretVisible(bool caret_is_visible) {
  frame_caret_->SetCaretVisibility(caret_is_visible ? CaretVisibility::kVisible
                                                    : CaretVisibility::kHidden);
}
