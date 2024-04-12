void RenderWidgetHostViewAura::CopyFromSurface(
    const gfx::Rect& src_subrect,
    const gfx::Size& dst_size,
    const ReadbackRequestCallback& callback,
    const SkColorType preferred_color_type) {
  if (!IsSurfaceAvailableForCopy()) {
    callback.Run(SkBitmap(), READBACK_SURFACE_UNAVAILABLE);
    return;
  }
  delegated_frame_host_->CopyFromCompositingSurface(
      src_subrect, dst_size, callback, preferred_color_type);
}
