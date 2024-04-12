HTMLCollection* Document::anchors()
{
    return ensureCachedCollection<HTMLCollection>(DocAnchors);
}
