static inline CanvasImageSource* ToImageSourceInternal(
    const CanvasImageSourceUnion& value,
    ExceptionState& exception_state) {
  if (value.IsCSSImageValue()) {
    if (RuntimeEnabledFeatures::CSSPaintAPIEnabled())
      return value.GetAsCSSImageValue();
    exception_state.ThrowTypeError("CSSImageValue is not yet supported");
    return nullptr;
  }
  if (value.IsHTMLImageElement())
    return value.GetAsHTMLImageElement();
  if (value.IsHTMLVideoElement()) {
    HTMLVideoElement* video = value.GetAsHTMLVideoElement();
    video->VideoWillBeDrawnToCanvas();
    return video;
  }
  if (value.IsSVGImageElement())
    return value.GetAsSVGImageElement();
  if (value.IsHTMLCanvasElement())
    return value.GetAsHTMLCanvasElement();
  if (value.IsImageBitmap()) {
    if (static_cast<ImageBitmap*>(value.GetAsImageBitmap())->IsNeutered()) {
      exception_state.ThrowDOMException(
          kInvalidStateError, String::Format("The image source is detached"));
      return nullptr;
    }
    return value.GetAsImageBitmap();
  }
  if (value.IsOffscreenCanvas()) {
    if (static_cast<OffscreenCanvas*>(value.GetAsOffscreenCanvas())
            ->IsNeutered()) {
      exception_state.ThrowDOMException(
          kInvalidStateError, String::Format("The image source is detached"));
      return nullptr;
    }
    return value.GetAsOffscreenCanvas();
  }
  NOTREACHED();
  return nullptr;
}
