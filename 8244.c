void Document::clearAXObjectCache()
{
    ASSERT(&axObjectCacheOwner() == this);
    m_axObjectCache.clear();
}
