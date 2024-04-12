WebLayer* WebGLRenderingContextBase::PlatformLayer() const {
  return isContextLost() ? 0 : GetDrawingBuffer()->PlatformLayer();
}
