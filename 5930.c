void SkiaOutputSurfaceImpl::SetDrawRectangle(const gfx::Rect& draw_rectangle) {
  DCHECK_CALLED_ON_VALID_THREAD(thread_checker_);
  DCHECK(capabilities().supports_dc_layers);
  DCHECK(!draw_rectangle_);
  draw_rectangle_.emplace(draw_rectangle);
}
