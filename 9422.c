Rect DIPToScreenRect(const Rect& dip_bounds) {
  return ToFlooredRectDeprecated(
      ScaleRect(dip_bounds, GetDeviceScaleFactor()));
}
