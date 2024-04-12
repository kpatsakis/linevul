void WebPluginProxy::CreateDIBAndCanvasFromHandle(
    const TransportDIB::Handle& dib_handle,
    const gfx::Rect& window_rect,
    scoped_ptr<TransportDIB>* dib_out,
    scoped_ptr<skia::PlatformCanvas>* canvas_out) {
  TransportDIB* dib = TransportDIB::Map(dib_handle);
  skia::PlatformCanvas* canvas = NULL;
  if (dib) {
    canvas = dib->GetPlatformCanvas(window_rect.width(), window_rect.height());
  }
  dib_out->reset(dib);
  canvas_out->reset(canvas);
}
