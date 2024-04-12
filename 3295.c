void SynchronizeVisualPropertiesMessageFilter::OnUpdatedFrameRectOnUI(
    const gfx::Rect& rect) {
  last_rect_ = rect;
  if (!screen_space_rect_received_) {
    screen_space_rect_received_ = true;
    screen_space_rect_run_loop_->QuitWhenIdle();
  }
}
