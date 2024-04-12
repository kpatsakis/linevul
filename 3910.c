const KURL& DocumentLoader::unreachableURL() const
{
    return m_substituteData.failingURL();
}
