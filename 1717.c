void FrameLoaderClient::postProgressStartedNotification()
{
    WebKitWebView* webView = getViewFromFrame(m_frame);
    g_signal_emit_by_name(webView, "load-started", m_frame);

    g_object_notify(G_OBJECT(webView), "progress");
}
