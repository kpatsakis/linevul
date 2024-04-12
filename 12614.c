void WebPagePrivate::resumeRootLayerCommit()
{
    if (!m_suspendRootLayerCommit)
        return;

    m_suspendRootLayerCommit = false;
    m_needsCommit = true;
}
