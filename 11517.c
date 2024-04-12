void WebPluginDelegateProxy::CopyFromTransportToBacking(const gfx::Rect& rect) {
  if (!backing_store_canvas_.get()) {
    return;
  }

#if defined(OS_MACOSX)
  const size_t stride =
      skia::PlatformCanvas::StrideForWidth(plugin_rect_.width());
  const size_t chunk_size = 4 * rect.width();
  uint8* source_data = static_cast<uint8*>(transport_store_->memory()) +
                       rect.y() * stride + 4 * rect.x();
  int dest_starting_row = plugin_rect_.height() - rect.y() - 1;
  DCHECK(backing_store_.size() > 0);
  uint8* target_data = &(backing_store_[0]) + dest_starting_row * stride +
                       4 * rect.x();
  for (int row = 0; row < rect.height(); ++row) {
    memcpy(target_data, source_data, chunk_size);
    source_data += stride;
    target_data -= stride;
  }
#else
  BlitCanvasToCanvas(backing_store_canvas_.get(), rect,
                     transport_store_canvas_.get(), rect.origin());
#endif
  backing_store_painted_ = backing_store_painted_.Union(rect);
}
