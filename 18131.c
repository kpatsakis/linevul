WebKitLoadStatus webkit_web_view_get_load_status(WebKitWebView* webView)
{
    g_return_val_if_fail(WEBKIT_IS_WEB_VIEW(webView), WEBKIT_LOAD_FINISHED);

    WebKitWebViewPrivate* priv = webView->priv;
    return priv->loadStatus;
}
