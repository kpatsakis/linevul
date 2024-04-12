static void on_sensitive_ticket_clicked_cb(GtkWidget *button, gpointer user_data)
{
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button)))
    {
        xsetenv(CREATE_PRIVATE_TICKET, "1");
    }
    else
    {
        safe_unsetenv(CREATE_PRIVATE_TICKET);
    }
}
