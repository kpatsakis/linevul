void WebGLRenderingContextBase::PushFrame() {
  int width = GetDrawingBuffer()->Size().Width();
  int height = GetDrawingBuffer()->Size().Height();
  if (PaintRenderingResultsToCanvas(kBackBuffer)) {
    if (Host()->GetOrCreateCanvasResourceProvider(kPreferAcceleration)) {
      Host()->PushFrame(Host()->ResourceProvider()->ProduceCanvasResource(),
                        SkIRect::MakeWH(width, height));
    }
  }
  MarkLayerComposited();
}
