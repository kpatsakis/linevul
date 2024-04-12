void InspectorPageAgent::didResizeMainFrame()
{
#if !OS(ANDROID)
    if (m_enabled && m_state->getBoolean(PageAgentState::showSizeOnResize))
        m_overlay->showAndHideViewSize(m_state->getBoolean(PageAgentState::showGridOnResize));
#endif
    m_frontend->frameResized();
}
