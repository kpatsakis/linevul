ImageBitmap* WebGLRenderingContextBase::TransferToImageBitmapBase(
    ScriptState* script_state) {
  WebFeature feature = WebFeature::kOffscreenCanvasTransferToImageBitmapWebGL;
  UseCounter::Count(ExecutionContext::From(script_state), feature);
  if (!GetDrawingBuffer())
    return nullptr;
  return ImageBitmap::Create(GetDrawingBuffer()->TransferToStaticBitmapImage());
}
