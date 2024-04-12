static gboolean webkit_web_view_focus_in_event(GtkWidget* widget, GdkEventFocus* event)
{
    GtkWidget* toplevel = gtk_widget_get_toplevel(widget);
    if (gtk_widget_is_toplevel(toplevel) && gtk_window_has_toplevel_focus(GTK_WINDOW(toplevel))) {
        WebKitWebView* webView = WEBKIT_WEB_VIEW(widget);
        FocusController* focusController = core(webView)->focusController();

        focusController->setActive(true);

        if (focusController->focusedFrame())
            focusController->setFocused(true);
        else
            focusController->setFocusedFrame(core(webView)->mainFrame());

        if (focusController->focusedFrame()->editor()->canEdit())
            gtk_im_context_focus_in(webView->priv->imContext.get());
    }
    return GTK_WIDGET_CLASS(webkit_web_view_parent_class)->focus_in_event(widget, event);
}
