void ShelfWidget::DelegateView::UpdateBackgroundBlur() {
  const bool should_blur_background =
      opaque_background_.visible() &&
      shelf_widget_->shelf_layout_manager()->ShouldBlurShelfBackground();
  if (should_blur_background == background_is_currently_blurred_)
    return;

  opaque_background_.SetBackgroundBlur(should_blur_background ? kShelfBlurRadius
                                                              : 0);
  opaque_background_.SetBackdropFilterQuality(kShelfBlurQuality);

  background_is_currently_blurred_ = should_blur_background;
}
