bool WebPluginDelegateProxy::BackgroundChanged(
    gfx::NativeDrawingContext context,
    const gfx::Rect& rect) {
#if defined(OS_ANDROID)
  NOTIMPLEMENTED();
#else
#if defined(OS_WIN)
  HBITMAP hbitmap = static_cast<HBITMAP>(GetCurrentObject(context, OBJ_BITMAP));
  if (hbitmap == NULL) {
    NOTREACHED();
    return true;
  }

  BITMAP bitmap = { 0 };
  int result = GetObject(hbitmap, sizeof(bitmap), &bitmap);
  if (!result) {
    NOTREACHED();
    return true;
  }

  XFORM xf;
  if (!GetWorldTransform(context, &xf)) {
    NOTREACHED();
    return true;
  }

  gfx::Rect bitmap_rect(static_cast<int>(-xf.eDx), static_cast<int>(-xf.eDy),
                        bitmap.bmWidth, bitmap.bmHeight);
  gfx::Rect check_rect = rect.Intersect(bitmap_rect);
  int row_byte_size = check_rect.width() * (bitmap.bmBitsPixel / 8);
  for (int y = check_rect.y(); y < check_rect.bottom(); y++) {
    char* hdc_row_start = static_cast<char*>(bitmap.bmBits) +
        (y + static_cast<int>(xf.eDy)) * bitmap.bmWidthBytes +
        (check_rect.x() + static_cast<int>(xf.eDx)) * (bitmap.bmBitsPixel / 8);

    uint32_t* canvas_row_start =
        background_store_.canvas->getDevice()->accessBitmap(true).getAddr32(
            check_rect.x() - plugin_rect_.x(), y - plugin_rect_.y());
    if (memcmp(hdc_row_start, canvas_row_start, row_byte_size) != 0)
      return true;
  }
#else
#if defined(OS_MACOSX)
  CGAffineTransform transform = CGContextGetCTM(context);
  bool flipped = fabs(transform.d + 1) < 0.0001;
  CGFloat context_offset_x = -transform.tx;
  CGFloat context_offset_y = flipped ? transform.ty -
                                           CGBitmapContextGetHeight(context)
                                     : -transform.ty;
  gfx::Rect full_content_rect(context_offset_x, context_offset_y,
                              CGBitmapContextGetWidth(context),
                              CGBitmapContextGetHeight(context));
#else
  cairo_surface_t* page_surface = cairo_get_target(context);
  DCHECK_EQ(cairo_surface_get_type(page_surface), CAIRO_SURFACE_TYPE_IMAGE);
  DCHECK_EQ(cairo_image_surface_get_format(page_surface), CAIRO_FORMAT_ARGB32);

  double page_x_double = rect.x();
  double page_y_double = rect.y();
  cairo_user_to_device(context, &page_x_double, &page_y_double);
  gfx::Rect full_content_rect(0, 0,
                              cairo_image_surface_get_width(page_surface),
                              cairo_image_surface_get_height(page_surface));
#endif
  gfx::Rect content_rect = rect.Intersect(full_content_rect);

#if defined(OS_MACOSX)
  const unsigned char* page_bytes = static_cast<const unsigned char*>(
      CGBitmapContextGetData(context));
  int page_stride = CGBitmapContextGetBytesPerRow(context);
  int page_start_x = content_rect.x() - context_offset_x;
  int page_start_y = content_rect.y() - context_offset_y;

  skia::ScopedPlatformPaint scoped_platform_paint(
      background_store_.canvas.get());
  CGContextRef bg_context = scoped_platform_paint.GetPlatformSurface();

  DCHECK_EQ(CGBitmapContextGetBitsPerPixel(context),
            CGBitmapContextGetBitsPerPixel(bg_context));
  const unsigned char* bg_bytes = static_cast<const unsigned char*>(
      CGBitmapContextGetData(bg_context));
  int full_bg_width = CGBitmapContextGetWidth(bg_context);
  int full_bg_height = CGBitmapContextGetHeight(bg_context);
  int bg_stride = CGBitmapContextGetBytesPerRow(bg_context);
  int bg_last_row = CGBitmapContextGetHeight(bg_context) - 1;

  int bytes_per_pixel = CGBitmapContextGetBitsPerPixel(context) / 8;
#else
  cairo_surface_flush(page_surface);
  const unsigned char* page_bytes = cairo_image_surface_get_data(page_surface);
  int page_stride = cairo_image_surface_get_stride(page_surface);
  int page_start_x = static_cast<int>(page_x_double);
  int page_start_y = static_cast<int>(page_y_double);

  skia::ScopedPlatformPaint scoped_platform_paint(
      background_store_.canvas.get());
  cairo_surface_t* bg_surface =cairo_get_target(
      scoped_platform_paint.GetPlatformSurface());
  DCHECK_EQ(cairo_surface_get_type(bg_surface), CAIRO_SURFACE_TYPE_IMAGE);
  DCHECK_EQ(cairo_image_surface_get_format(bg_surface), CAIRO_FORMAT_ARGB32);
  cairo_surface_flush(bg_surface);
  const unsigned char* bg_bytes = cairo_image_surface_get_data(bg_surface);
  int full_bg_width = cairo_image_surface_get_width(bg_surface);
  int full_bg_height = cairo_image_surface_get_height(bg_surface);
  int bg_stride = cairo_image_surface_get_stride(bg_surface);

  int bytes_per_pixel = 4;  // ARGB32 = 4 bytes per pixel.
#endif

  int damage_width = content_rect.width();
  int damage_height = content_rect.height();

  int bg_start_x = rect.x() - plugin_rect_.x();
  int bg_start_y = rect.y() - plugin_rect_.y();
  DCHECK_LE(bg_start_x + damage_width, full_bg_width);
  DCHECK_LE(bg_start_y + damage_height, full_bg_height);

  int bg_x_byte_offset = bg_start_x * bytes_per_pixel;
  int page_x_byte_offset = page_start_x * bytes_per_pixel;
  for (int row = 0; row < damage_height; ++row) {
    int page_offset = page_stride * (page_start_y + row) + page_x_byte_offset;
    int bg_y = bg_start_y + row;
#if defined(OS_MACOSX)
    bg_y = bg_last_row - bg_y;
#endif
    int bg_offset = bg_stride * bg_y + bg_x_byte_offset;
    if (memcmp(page_bytes + page_offset,
               bg_bytes + bg_offset,
               damage_width * bytes_per_pixel) != 0)
      return true;
  }
#endif
#endif  // OS_ANDROID

  return false;
}
