CanvasRenderingContextFactory* OffscreenCanvas::GetRenderingContextFactory(
    int type) {
  DCHECK_LE(type, CanvasRenderingContext::kMaxValue);
  return RenderingContextFactories()[type].get();
}
