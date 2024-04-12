bool BaseRenderingContext2D::ComputeDirtyRect(const FloatRect& local_rect,
                                              SkIRect* dirty_rect) {
  SkIRect clip_bounds;
  if (!DrawingCanvas()->getDeviceClipBounds(&clip_bounds))
    return false;
  return ComputeDirtyRect(local_rect, clip_bounds, dirty_rect);
}
