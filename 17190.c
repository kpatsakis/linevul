scoped_refptr<StaticBitmapImage> WebGLRenderingContextBase::GetImage(
    AccelerationHint hint) const {
  if (!GetDrawingBuffer())
    return nullptr;
  GetDrawingBuffer()->ResolveAndBindForReadAndDraw();
  IntSize size = ClampedCanvasSize();
  std::unique_ptr<CanvasResourceProvider> resource_provider =
      CanvasResourceProvider::Create(
          size, CanvasResourceProvider::kAcceleratedResourceUsage,
          SharedGpuContext::ContextProviderWrapper(), 0, ColorParams());
  if (!resource_provider || !resource_provider->IsValid())
    return nullptr;
  if (!CopyRenderingResultsFromDrawingBuffer(resource_provider.get(),
                                             kBackBuffer)) {
    NOTREACHED();
    return nullptr;
  }
  return resource_provider->Snapshot();
}
