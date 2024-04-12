void WebPageProxy::missingPluginButtonClicked(const String& mimeType, const String& url, const String& pluginsPageURL)
{
    m_uiClient.missingPluginButtonClicked(this, mimeType, url, pluginsPageURL);
}
