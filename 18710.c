bool RenderWidgetHostViewAura::TransformPointToLocalCoordSpace(
    const gfx::Point& point,
    const cc::SurfaceId& original_surface,
    gfx::Point* transformed_point) {
  gfx::Point point_in_pixels =
      gfx::ConvertPointToPixel(device_scale_factor_, point);
  if (delegated_frame_host_ &&
      !delegated_frame_host_->TransformPointToLocalCoordSpace(
          point_in_pixels, original_surface, transformed_point))
    return false;
  *transformed_point =
      gfx::ConvertPointToDIP(device_scale_factor_, *transformed_point);
  return true;
}
