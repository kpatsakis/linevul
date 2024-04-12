void PaletteTray::HideBubbleWithView(const views::TrayBubbleView* bubble_view) {
  if (bubble_->bubble_view() == bubble_view)
    bubble_.reset();
}
