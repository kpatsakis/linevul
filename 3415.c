void Document::clearAXObjectCache()
{
    ASSERT(&axObjectCacheOwner() == this);
    if (m_axObjectCache)
        m_axObjectCache->dispose();
    m_axObjectCache.clear();
}
