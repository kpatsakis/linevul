static void webkit_web_view_dispose(GObject* object)
{
    WebKitWebView* webView = WEBKIT_WEB_VIEW(object);
    WebKitWebViewPrivate* priv = webView->priv;

    priv->disposing = TRUE;

    priv->backForwardList.clear();

    if (priv->corePage) {
        webkit_web_view_stop_loading(WEBKIT_WEB_VIEW(object));
        core(priv->mainFrame)->loader()->detachFromParent();
        delete priv->corePage;
        priv->corePage = 0;
    }

    if (priv->webSettings) {
        g_signal_handlers_disconnect_by_func(priv->webSettings.get(), (gpointer)webkit_web_view_settings_notify, webView);
        priv->webSettings.clear();
    }

    if (priv->currentMenu) {
        gtk_widget_destroy(GTK_WIDGET(priv->currentMenu));
        priv->currentMenu = 0;
    }

    priv->webInspector.clear();
    priv->viewportAttributes.clear();
    priv->webWindowFeatures.clear();
    priv->mainResource.clear();
    priv->subResources.clear();

    HashMap<GdkDragContext*, DroppingContext*>::iterator endDroppingContexts = priv->droppingContexts.end();
    for (HashMap<GdkDragContext*, DroppingContext*>::iterator iter = priv->droppingContexts.begin(); iter != endDroppingContexts; ++iter)
        delete (iter->second);
    priv->droppingContexts.clear();

    G_OBJECT_CLASS(webkit_web_view_parent_class)->dispose(object);
}
