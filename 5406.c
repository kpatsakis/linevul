void WebInspectorProxy::platformOpen()
{
    ASSERT(!m_inspectorWindow);
    ASSERT(m_inspectorView);

    if (m_isAttached)
        platformAttach();
    else
        createInspectorWindow();
    g_signal_connect(m_inspectorView, "destroy", G_CALLBACK(inspectorViewDestroyed), this);
}
