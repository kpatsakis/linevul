  static gboolean OnConfigureEvent(GtkWidget* widget,
                                   GdkEventConfigure* event,
                                   RenderWidgetHostViewGtk* host_view) {
    host_view->MarkCachedWidgetCenterStale();
    host_view->UpdateScreenInfo(host_view->GetNativeView());
    return FALSE;
  }
