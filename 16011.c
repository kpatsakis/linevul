    void setUrlToLoad(const String& value, URLReplacement replacement)
    {
        if (replacement == DisallowURLReplacement && !m_urlToLoad.isEmpty())
            return;
        String url = stripLeadingAndTrailingHTMLSpaces(value);
        if (url.isEmpty())
            return;
        m_urlToLoad = url;
    }
