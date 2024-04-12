void WebPluginDelegatePepper::Paint(WebKit::WebCanvas* canvas,
                                    const gfx::Rect& rect) {
#if defined(OS_WIN) || defined(OS_LINUX)
  if (nested_delegate_) {
  } else {
    if (!committed_bitmap_.isNull()) {
      gfx::Point origin(window_rect_.origin().x(), window_rect_.origin().y());
      canvas->drawBitmap(committed_bitmap_,
                         SkIntToScalar(window_rect_.origin().x()),
                         SkIntToScalar(window_rect_.origin().y()));
    }
  }
#endif
}
