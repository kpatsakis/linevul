void Document::setBaseURLOverride(const KURL& url)
{
    m_baseURLOverride = url;
    updateBaseURL();
}
