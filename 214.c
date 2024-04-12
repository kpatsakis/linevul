void WebPageProxy::didReceiveMessage(CoreIPC::Connection* connection, CoreIPC::MessageID messageID, CoreIPC::ArgumentDecoder* arguments)
{
#if PLATFORM(MAC) || PLATFORM(WIN)
    if (messageID.is<CoreIPC::MessageClassDrawingAreaProxy>()) {
        m_drawingArea->didReceiveDrawingAreaProxyMessage(connection, messageID, arguments);
        return;
    }
#endif

    if (messageID.is<CoreIPC::MessageClassDrawingAreaProxyLegacy>()) {
        m_drawingArea->didReceiveMessage(connection, messageID, arguments);
        return;
    }

#if ENABLE(INSPECTOR)
    if (messageID.is<CoreIPC::MessageClassWebInspectorProxy>()) {
        if (WebInspectorProxy* inspector = this->inspector())
            inspector->didReceiveWebInspectorProxyMessage(connection, messageID, arguments);
        return;
    }
#endif

#if ENABLE(FULLSCREEN_API)
    if (messageID.is<CoreIPC::MessageClassWebFullScreenManagerProxy>()) {
        fullScreenManager()->didReceiveMessage(connection, messageID, arguments);
        return;
    }
#endif

    didReceiveWebPageProxyMessage(connection, messageID, arguments);
}
