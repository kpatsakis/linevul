HTMLScriptRunner::~HTMLScriptRunner()
{
#if ENABLE(OILPAN)
    detach();
#else
    ASSERT(!m_document);
#endif
}
