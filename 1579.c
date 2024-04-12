gboolean TabStripGtk::OnDragDrop(GtkWidget* widget, GdkDragContext* context,
                                 gint x, gint y, guint time) {
  if (!drop_info_.get())
    return FALSE;

  GdkAtom target = gtk_drag_dest_find_target(widget, context, NULL);
  if (target != GDK_NONE)
    gtk_drag_finish(context, FALSE, FALSE, time);
  else
    gtk_drag_get_data(widget, context, target, time);

  return TRUE;
}
