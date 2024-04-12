scoped_refptr<StaticBitmapImage> WebGLRenderingContextBase::GetImage(
    AccelerationHint hint) const {
  if (!GetDrawingBuffer())
    return nullptr;
  if (IsMainThread()) {
    GetDrawingBuffer()->ResolveAndBindForReadAndDraw();
    IntSize size = ClampedCanvasSize();
    std::unique_ptr<AcceleratedImageBufferSurface> surface =
        std::make_unique<AcceleratedImageBufferSurface>(size, ColorParams());
    if (!surface->IsValid())
      return nullptr;
    if (!CopyRenderingResultsFromDrawingBuffer(surface.get(), kBackBuffer)) {
      NOTREACHED();
      return nullptr;
    }
    return surface->NewImageSnapshot(hint);
  }

  int width = GetDrawingBuffer()->Size().Width();
  int height = GetDrawingBuffer()->Size().Height();
  SkImageInfo image_info = SkImageInfo::Make(
      width, height, kRGBA_8888_SkColorType,
      CreationAttributes().alpha() ? kPremul_SkAlphaType : kOpaque_SkAlphaType);
  return this->MakeImageSnapshot(image_info);
}
