static void webkitWebViewBaseSizeAllocate(GtkWidget* widget, GtkAllocation* allocation)
{
    GTK_WIDGET_CLASS(webkit_web_view_base_parent_class)->size_allocate(widget, allocation);

    WebKitWebViewBase* webViewBase = WEBKIT_WEB_VIEW_BASE(widget);
    if (!gtk_widget_get_mapped(GTK_WIDGET(webViewBase)) && !webViewBase->priv->pageProxy->drawingArea()->size().isEmpty()) {
        webViewBase->priv->needsResizeOnMap = true;
        return;
    }
    resizeWebKitWebViewBaseFromAllocation(webViewBase, allocation);
}
