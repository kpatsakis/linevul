void WebPageProxy::didFindString(const String& string, uint32_t matchCount)
{
    m_findClient.didFindString(this, string, matchCount);
}
