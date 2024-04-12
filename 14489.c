void PlatformFontSkia::InitFromPlatformFont(const PlatformFontSkia* other) {
  TRACE_EVENT0("fonts", "PlatformFontSkia::InitFromPlatformFont");
  typeface_ = other->typeface_;
  font_family_ = other->font_family_;
  font_size_pixels_ = other->font_size_pixels_;
  style_ = other->style_;
  weight_ = other->weight_;
  device_scale_factor_ = other->device_scale_factor_;
  font_render_params_ = other->font_render_params_;

  if (!other->metrics_need_computation_) {
    metrics_need_computation_ = false;
    ascent_pixels_ = other->ascent_pixels_;
    height_pixels_ = other->height_pixels_;
    cap_height_pixels_ = other->cap_height_pixels_;
    average_width_pixels_ = other->average_width_pixels_;
  }
}
