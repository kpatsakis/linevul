static void run_event_gtk_alert(const char *msg, void *args)
{
    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(g_wnd_assistant),
            GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_WARNING,
            GTK_BUTTONS_CLOSE,
            "%s", msg);
    char *tagged_msg = tag_url(msg, "\n");
    gtk_message_dialog_set_markup(GTK_MESSAGE_DIALOG(dialog), tagged_msg);
    free(tagged_msg);

    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

    log_request_response_communication(msg, NULL, (struct analyze_event_data *)args);
}
