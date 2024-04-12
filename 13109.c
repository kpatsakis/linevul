GdkCursor* GetMozSpinningCursor() {
  static GdkCursor* moz_spinning_cursor = NULL;
  if (!moz_spinning_cursor) {
    const GdkColor fg = { 0, 0, 0, 0 };
    const GdkColor bg = { 65535, 65535, 65535, 65535 };
    GdkPixmap* source = gdk_bitmap_create_from_data(
        NULL, reinterpret_cast<const gchar*>(moz_spinning_bits), 32, 32);
    GdkPixmap* mask = gdk_bitmap_create_from_data(
        NULL, reinterpret_cast<const gchar*>(moz_spinning_mask_bits), 32, 32);
    moz_spinning_cursor =
        gdk_cursor_new_from_pixmap(source, mask, &fg, &bg, 2, 2);
    g_object_unref(source);
    g_object_unref(mask);
  }
  return moz_spinning_cursor;
}
