create_mainbar () {
    GUI *g = &uzbl.gui;

    g->mainbar = gtk_hbox_new (FALSE, 0);
    g->mainbar_label = gtk_label_new ("");
    gtk_label_set_selectable((GtkLabel *)g->mainbar_label, TRUE);
    gtk_label_set_ellipsize(GTK_LABEL(g->mainbar_label), PANGO_ELLIPSIZE_END);
    gtk_misc_set_alignment (GTK_MISC(g->mainbar_label), 0, 0);
    gtk_misc_set_padding (GTK_MISC(g->mainbar_label), 2, 2);
    gtk_box_pack_start (GTK_BOX (g->mainbar), g->mainbar_label, TRUE, TRUE, 0);

    g_object_connect((GObject*)g->mainbar,
      "signal::key-press-event",                    (GCallback)key_press_cb,    NULL,
      "signal::key-release-event",                  (GCallback)key_release_cb,  NULL,
      NULL);

    return g->mainbar;
}
