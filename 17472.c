void WebGLRenderingContextBase::getHTMLOrOffscreenCanvas(
    HTMLCanvasElementOrOffscreenCanvas& result) const {
  if (canvas()) {
    result.SetHTMLCanvasElement(static_cast<HTMLCanvasElement*>(Host()));
  } else {
    result.SetOffscreenCanvas(static_cast<OffscreenCanvas*>(Host()));
  }
}
