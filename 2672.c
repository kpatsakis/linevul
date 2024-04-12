void WebPluginDelegateProxy::Paint(WebKit::WebCanvas* canvas,
                                   const gfx::Rect& damaged_rect) {
  gfx::Rect rect = damaged_rect.Intersect(plugin_rect_);

  if (!channel_host_ || !channel_host_->channel_valid()) {
    PaintSadPlugin(canvas, rect);
    return;
  }

  if (!uses_shared_bitmaps_)
    return;

  if (!front_buffer_canvas())
    return;

#if WEBKIT_USING_SKIA
  if (!skia::SupportsPlatformPaint(canvas)) {
    DLOG(WARNING) << "Could not paint plugin";
    return;
  }
  skia::ScopedPlatformPaint scoped_platform_paint(canvas);
  gfx::NativeDrawingContext context =
      scoped_platform_paint.GetPlatformSurface();
#elif WEBKIT_USING_CG
  gfx::NativeDrawingContext context = canvas;
#endif

  gfx::Rect offset_rect = rect;
  offset_rect.Offset(-plugin_rect_.x(), -plugin_rect_.y());
  gfx::Rect canvas_rect = offset_rect;
#if defined(OS_MACOSX)
  FlipRectVerticallyWithHeight(&canvas_rect, plugin_rect_.height());
#endif

  bool background_changed = false;
  if (background_store_.canvas.get() && BackgroundChanged(context, rect)) {
    background_changed = true;
    BlitContextToCanvas(background_store_.canvas.get(), canvas_rect,
                        context, rect.origin());
  }

  if (background_changed ||
      !transport_store_painted_.Contains(offset_rect)) {
    Send(new PluginMsg_Paint(instance_id_, offset_rect));
    UpdateFrontBuffer(offset_rect, false);
  }

#if defined(OS_MACOSX)
  CGContextSaveGState(context);
  CGContextScaleCTM(context, 1, -1);
  rect.set_y(-rect.bottom());
#endif
  BlitCanvasToContext(context,
                      rect,
                      front_buffer_canvas(),
                      offset_rect.origin());
#if defined(OS_MACOSX)
  CGContextRestoreGState(context);
#endif

  if (invalidate_pending_) {
    invalidate_pending_ = false;
    Send(new PluginMsg_DidPaint(instance_id_));
  }
}
