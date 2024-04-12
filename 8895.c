PassRefPtr<HTMLCollection> Document::plugins()
{
    return ensureCachedCollection(DocEmbeds);
}
