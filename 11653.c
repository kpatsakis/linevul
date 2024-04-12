void TabStrip::UpdateContrastRatioValues() {
  if (!controller_)
    return;

  const SkColor inactive_bg = GetTabBackgroundColor(TAB_INACTIVE);
  const auto get_alpha = [inactive_bg](SkColor target, float contrast) {
    return color_utils::GetBlendValueWithMinimumContrast(inactive_bg, target,
                                                         inactive_bg, contrast);
  };

  const SkColor active_bg = GetTabBackgroundColor(TAB_ACTIVE);
  const auto get_hover_opacity = [active_bg, &get_alpha](float contrast) {
    return get_alpha(active_bg, contrast) / 255.0f;
  };

  constexpr float kStandardWidthContrast = 1.11f;
  hover_opacity_min_ = get_hover_opacity(kStandardWidthContrast);

  constexpr float kMinWidthContrast = 1.19f;
  hover_opacity_max_ = get_hover_opacity(kMinWidthContrast);

  constexpr float kRadialGradientContrast = 1.13728f;
  radial_highlight_opacity_ = get_hover_opacity(kRadialGradientContrast);

  const SkColor inactive_fg = GetTabForegroundColor(TAB_INACTIVE, inactive_bg);
  constexpr float kTabSeparatorContrast = 2.5f;
  const SkAlpha separator_alpha = get_alpha(inactive_fg, kTabSeparatorContrast);
  separator_color_ =
      color_utils::AlphaBlend(inactive_fg, inactive_bg, separator_alpha);
}
