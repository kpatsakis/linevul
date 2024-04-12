bool WebPagePrivate::shouldSendResizeEvent()
{
    if (!m_mainFrame->document())
        return false;

    static const bool unrestrictedResizeEvents = Platform::Settings::instance()->unrestrictedResizeEvents();
    if (unrestrictedResizeEvents)
        return true;

    DocumentLoader* documentLoader = m_mainFrame->loader()->documentLoader();
    if (documentLoader && documentLoader->isLoadingInAPISense())
        return false;

    return true;
}
