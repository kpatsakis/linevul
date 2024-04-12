void Document::setImportsController(HTMLImportsController* controller)
{
    ASSERT(!m_importsController || !controller);
    m_importsController = controller;
    if (!m_importsController && !loader())
        m_fetcher->clearContext();
}
