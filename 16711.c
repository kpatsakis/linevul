void RenderWidgetHostViewAura::SetInsets(const gfx::Insets& insets) {
  if (insets != insets_) {
    insets_ = insets;
    host_->WasResized();
  }
}
