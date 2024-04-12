SkColor GetBaseColor(SkColor color) {
  return SkColorSetRGB(SkColorGetR(color), SkColorGetG(color),
                       SkColorGetB(color));
}
