void PaintController::EnsureRasterInvalidationTracking() {
  if (!raster_invalidation_tracking_info_) {
    raster_invalidation_tracking_info_ =
        std::make_unique<RasterInvalidationTrackingInfo>();
  }
}
