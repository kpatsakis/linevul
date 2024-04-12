HTMLCollection* Document::scripts()
{
    return ensureCachedCollection<HTMLCollection>(DocScripts);
}
