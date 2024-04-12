void BrowserActionsContainer::OnResize(int resize_amount, bool done_resizing) {
  if (!done_resizing) {
    resize_amount_ = resize_amount;
    OnBrowserActionVisibilityChanged();
  } else {

    int new_width = std::max(0, container_size_.width() - resize_amount);
    int max_width = ClampToNearestIconCount(-1);
    new_width = std::min(new_width, max_width);

    container_size_.set_width(new_width);
    animation_target_size_ = ClampToNearestIconCount(new_width);
    resize_animation_->Reset();
    resize_animation_->SetTweenType(SlideAnimation::EASE_OUT);
    resize_animation_->Show();
  }
}
