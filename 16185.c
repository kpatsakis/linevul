void InspectorResourceAgent::clearBrowserCache(ErrorString*)
{
    m_client->clearBrowserCache();
}
