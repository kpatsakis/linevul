inline Range::Range(PassRefPtr<Document> ownerDocument)
    : m_ownerDocument(ownerDocument)
    , m_start(m_ownerDocument)
    , m_end(m_ownerDocument)
{
#ifndef NDEBUG
    rangeCounter.increment();
#endif

    m_ownerDocument->attachRange(this);
}
