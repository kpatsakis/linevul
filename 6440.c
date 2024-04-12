ViewportDescription Document::viewportDescription() const
{
    ViewportDescription appliedViewportDescription = m_viewportDescription;
    bool viewportMetaEnabled = settings() && settings()->viewportMetaEnabled();
    if (m_legacyViewportDescription.type != ViewportDescription::UserAgentStyleSheet && viewportMetaEnabled)
        appliedViewportDescription = m_legacyViewportDescription;
    if (shouldOverrideLegacyDescription(m_viewportDescription.type))
        appliedViewportDescription = m_viewportDescription;

    return appliedViewportDescription;
}
