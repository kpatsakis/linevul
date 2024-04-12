void WebPagePrivate::resetScales()
{
    TransformationMatrix identity;
    *m_transformationMatrix = identity;
    m_initialScale = m_webSettings->initialScale() > 0 ? m_webSettings->initialScale() : -1.0;
    m_minimumScale = -1.0;
    m_maximumScale = -1.0;

    updateViewportSize();
}
