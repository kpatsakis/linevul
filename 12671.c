void WebGLRenderingContextBase::OnBeforeDrawCall() {
  ClearIfComposited();
  MarkContextChanged(kCanvasChanged);
}
