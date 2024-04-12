void DocumentLoader::setRequest(const ResourceRequest& req)
{
    bool handlingUnreachableURL = false;

    handlingUnreachableURL = m_substituteData.isValid() && !m_substituteData.failingURL().isEmpty();

    if (handlingUnreachableURL)
        m_committed = false;

    ASSERT(!m_committed);

    m_request = req;
}
