static FloatRect ComputeRightDelta(const FloatPoint& location,
                                   const FloatSize& old_size,
                                   const FloatSize& new_size) {
  float delta = new_size.Width() - old_size.Width();
  if (delta > 0) {
    return FloatRect(location.X() + old_size.Width(), location.Y(), delta,
                     new_size.Height());
  }
  if (delta < 0) {
    return FloatRect(location.X() + new_size.Width(), location.Y(), -delta,
                     old_size.Height());
  }
  return FloatRect();
}
