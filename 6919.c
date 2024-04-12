open_with_response_cb (GtkDialog *dialog,
                       gint       response_id,
                       gpointer   user_data)
{
    GtkWindow *parent_window;
    NautilusFile *file;
    GList files;
    GAppInfo *info;
    ActivateParametersInstall *parameters = user_data;

    if (response_id != GTK_RESPONSE_OK)
    {
        gtk_widget_destroy (GTK_WIDGET (dialog));
        return;
    }

    parent_window = parameters->parent_window;
    file = g_object_get_data (G_OBJECT (dialog), "mime-action:file");
    info = gtk_app_chooser_get_app_info (GTK_APP_CHOOSER (dialog));

    gtk_widget_destroy (GTK_WIDGET (dialog));

    g_signal_emit_by_name (nautilus_signaller_get_current (), "mime-data-changed");

    files.next = NULL;
    files.prev = NULL;
    files.data = file;
    nautilus_launch_application (info, &files, parent_window);

    g_object_unref (info);

    activate_parameters_install_free (parameters);
}
