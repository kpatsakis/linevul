IntPoint WebPagePrivate::mapFromTransformedContentsToTransformedViewport(const IntPoint& point) const
{
    return m_backingStoreClient->mapFromTransformedContentsToTransformedViewport(point);
}
