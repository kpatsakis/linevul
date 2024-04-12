void InspectorResourceAgent::markResourceAsCached(unsigned long identifier)
{
    m_frontend->requestServedFromCache(IdentifiersFactory::requestId(identifier));
}
