gfx::ImageSkia NewTabButton::GetImageForScale(
    ui::ScaleFactor scale_factor) const {
  if (!hover_animation_->is_animating())
    return GetImageForState(state(), scale_factor);
  return gfx::ImageSkiaOperations::CreateBlendedImage(
      GetImageForState(views::CustomButton::STATE_NORMAL, scale_factor),
      GetImageForState(views::CustomButton::STATE_HOVERED, scale_factor),
      hover_animation_->GetCurrentValue());
}
