GdkColor NormalURLColor(GdkColor foreground) {
  color_utils::HSL fg_hsl;
  color_utils::SkColorToHSL(gfx::GdkColorToSkColor(foreground), &fg_hsl);

  color_utils::HSL hue_hsl;
  color_utils::SkColorToHSL(gfx::GdkColorToSkColor(kURLTextColor), &hue_hsl);

  double s = std::max(0.5, fg_hsl.s);

  double l;
  if (fg_hsl.l < hue_hsl.l)
    l = hue_hsl.l;
  else
    l = (fg_hsl.l + hue_hsl.l) / 2;

  color_utils::HSL output = { hue_hsl.h, s, l };
  return gfx::SkColorToGdkColor(color_utils::HSLToSkColor(output, 255));
}
