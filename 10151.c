void Document::updateBaseURL()
{
    KURL oldBaseURL = m_baseURL;
    if (!m_baseElementURL.isEmpty())
        m_baseURL = m_baseElementURL;
    else if (!m_baseURLOverride.isEmpty())
        m_baseURL = m_baseURLOverride;
    else
        m_baseURL = m_url;

    selectorQueryCache().invalidate();

    if (!m_baseURL.isValid())
        m_baseURL = KURL();

    if (m_elemSheet) {
        ASSERT(!m_elemSheet->contents()->ruleCount());
        m_elemSheet = CSSStyleSheet::createInline(this, m_baseURL);
    }

    if (!equalIgnoringFragmentIdentifier(oldBaseURL, m_baseURL)) {
        for (HTMLAnchorElement& anchor : Traversal<HTMLAnchorElement>::startsAfter(*this))
            anchor.invalidateCachedVisitedLinkHash();
    }
}
