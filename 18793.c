ImageBitmap* WebGLRenderingContextBase::TransferToImageBitmapBase(
    ScriptState* script_state) {
  WebFeature feature = WebFeature::kOffscreenCanvasTransferToImageBitmapWebGL;
  UseCounter::Count(ExecutionContext::From(script_state), feature);
  if (!GetDrawingBuffer())
    return nullptr;
  std::unique_ptr<viz::SingleReleaseCallback> image_release_callback;
  scoped_refptr<StaticBitmapImage> image =
      GetDrawingBuffer()->TransferToStaticBitmapImage(&image_release_callback);
  GetDrawingBuffer()->SwapPreviousFrameCallback(
      std::move(image_release_callback));

  return ImageBitmap::Create(image);
}
