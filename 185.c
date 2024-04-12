void PanelBrowserView::AnimationEnded(const ui::Animation* animation) {
  panel_->manager()->OnPanelAnimationEnded(panel_.get());
}
