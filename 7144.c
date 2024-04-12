void PaletteTray::BubbleViewDestroyed() {
  palette_tool_manager_->NotifyViewsDestroyed();
  SetDrawBackgroundAsActive(false);
}
