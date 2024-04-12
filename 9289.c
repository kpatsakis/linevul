bool WebPageProxy::supportsTextEncoding() const
{
    return !m_mainFrameHasCustomRepresentation && m_mainFrame && !m_mainFrame->isDisplayingStandaloneImageDocument();
}
