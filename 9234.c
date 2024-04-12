void webkit_web_view_set_zoom_level(WebKitWebView* webView, gfloat zoomLevel)
{
    g_return_if_fail(WEBKIT_IS_WEB_VIEW(webView));

    webkit_web_view_apply_zoom_level(webView, zoomLevel);
    g_object_notify(G_OBJECT(webView), "zoom-level");
}
