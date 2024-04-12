void FrameLoaderClient::dispatchDidChangeLocationWithinPage()
{
    WebKitWebFramePrivate* priv = m_frame->priv;
    g_free(priv->uri);
    priv->uri = g_strdup(core(m_frame)->loader()->url().prettyURL().utf8().data());
    g_object_notify(G_OBJECT(m_frame), "uri");
    WebKitWebView* webView = getViewFromFrame(m_frame);
    if (m_frame == webkit_web_view_get_main_frame(webView))
        g_object_notify(G_OBJECT(webView), "uri");
}
