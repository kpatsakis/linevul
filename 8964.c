IntSize WebGLRenderingContextBase::ClampedCanvasSize() const {
  int width = host()->Size().Width();
  int height = host()->Size().Height();
  return IntSize(Clamp(width, 1, max_viewport_dims_[0]),
                 Clamp(height, 1, max_viewport_dims_[1]));
}
