gboolean TabStripGtk::OnDragDataReceived(GtkWidget* widget,
                                         GdkDragContext* context,
                                         gint x, gint y,
                                         GtkSelectionData* data,
                                         guint info, guint time) {
  bool success = false;

  if (info == ui::TEXT_URI_LIST ||
      info == ui::NETSCAPE_URL ||
      info == ui::TEXT_PLAIN) {
    success = CompleteDrop(gtk_selection_data_get_data(data),
                           info == ui::TEXT_PLAIN);
  }

  gtk_drag_finish(context, success, FALSE, time);
  return TRUE;
}
