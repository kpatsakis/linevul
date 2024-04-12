void RenderWidgetHostViewAndroid::SetCachedPageScaleFactorLimits(
    float minimum_scale,
    float maximum_scale) {
  if (content_view_core_)
    content_view_core_->UpdatePageScaleLimits(minimum_scale, maximum_scale);
}
