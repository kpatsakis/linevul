bool Document::IsPageVisible() const {
  if (!frame_ || !frame_->GetPage())
    return false;
  if (load_event_progress_ >= kUnloadVisibilityChangeInProgress)
    return false;
  return frame_->GetPage()->IsPageVisible();
}
