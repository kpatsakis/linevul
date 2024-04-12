PassRefPtr<ArchiveResource> DocumentLoader::subresource(const KURL& url) const
{
    if (!isCommitted())
        return 0;
    
    CachedResource* resource = m_cachedResourceLoader->cachedResource(url);
    if (!resource || !resource->isLoaded())
        return archiveResourceForURL(url);

    if (resource->type() == CachedResource::MainResource)
        return 0;

    if (!resource->makePurgeable(false))
        return 0;

    ResourceBuffer* data = resource->resourceBuffer();
    if (!data)
        return 0;

    return ArchiveResource::create(data->sharedBuffer(), url, resource->response());
}
