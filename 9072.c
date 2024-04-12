void RenderViewImpl::OnZoomFactor(content::PageZoom zoom,
                                  int zoom_center_x, int zoom_center_y) {
  ZoomFactorHelper(zoom, zoom_center_x, zoom_center_y,
                   kScalingIncrementForGesture);
}
