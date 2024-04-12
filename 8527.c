gboolean webkit_web_view_can_go_back_or_forward(WebKitWebView* webView, gint steps)
{
    g_return_val_if_fail(WEBKIT_IS_WEB_VIEW(webView), FALSE);

    return core(webView)->canGoBackOrForward(steps);
}
