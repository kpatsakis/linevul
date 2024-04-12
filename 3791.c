void ResourceFetcher::trace(Visitor* visitor)
{
    visitor->trace(m_document);
    ResourceLoaderHost::trace(visitor);
}
