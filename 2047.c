GtkWidget* AddMenuEntry(GtkWidget* menu_widget, const char* text,
                        GCallback callback, Shell* shell) {
  GtkWidget* entry = gtk_menu_item_new_with_label(text);
  g_signal_connect(entry, "activate", callback, shell);
  gtk_menu_shell_append(GTK_MENU_SHELL(menu_widget), entry);
  return entry;
}
