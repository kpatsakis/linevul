const OriginAccessEntry& Document::accessEntryFromURL()
{
    if (!m_accessEntryFromURL) {
        m_accessEntryFromURL = wrapUnique(new OriginAccessEntry(url().protocol(), url().host(), OriginAccessEntry::AllowRegisterableDomains));
    }
    return *m_accessEntryFromURL;
}
