void BrowserWindowGtk::DrawPopupFrame(cairo_t* cr,
                                      GtkWidget* widget,
                                      GdkEventExpose* event) {
  ui::ResourceBundle& rb = ui::ResourceBundle::GetSharedInstance();

  int image_name = GetThemeFrameResource();
  gfx::CairoCachedSurface* surface =
      rb.GetNativeImageNamed(image_name).ToCairo();
  surface->SetSource(cr, widget, 0, GetVerticalOffset());
  cairo_pattern_set_extend(cairo_get_source(cr), CAIRO_EXTEND_REFLECT);
  cairo_rectangle(cr, event->area.x, event->area.y,
                  event->area.width, event->area.height);
  cairo_fill(cr);
}
