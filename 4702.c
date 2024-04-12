PassRefPtr<HTMLCollection> Document::links()
{
    return ensureCachedCollection(DocLinks);
}
