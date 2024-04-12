bool Document::CanCreateHistoryEntry() const {
  if (!GetSettings() || !GetSettings()->GetHistoryEntryRequiresUserGesture())
    return true;
  if (frame_->HasReceivedUserGesture())
    return true;
  return ElapsedTime() >= kElapsedTimeForHistoryEntryWithoutUserGestureMS;
}
