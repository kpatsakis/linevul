gfx::SwapResult GLSurfaceOzoneSurfacelessSurfaceImpl::SwapBuffers() {
  if (!images_[current_surface_]->ScheduleOverlayPlane(
          widget_, 0, OverlayTransform::OVERLAY_TRANSFORM_NONE,
          gfx::Rect(GetSize()), gfx::RectF(1, 1)))
    return gfx::SwapResult::SWAP_FAILED;
  gfx::SwapResult result = GLSurfaceOzoneSurfaceless::SwapBuffers();
  if (result != gfx::SwapResult::SWAP_ACK)
    return result;
  current_surface_ ^= 1;
  BindFramebuffer();
  return gfx::SwapResult::SWAP_ACK;
}
