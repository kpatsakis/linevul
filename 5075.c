bool InspectorPageAgent::deviceMetricsChanged(int width, int height, double deviceScaleFactor, bool emulateViewport, bool fitWindow, double fontScaleFactor, bool textAutosizing)
{
    int currentWidth = static_cast<int>(m_state->getLong(PageAgentState::pageAgentScreenWidthOverride));
    int currentHeight = static_cast<int>(m_state->getLong(PageAgentState::pageAgentScreenHeightOverride));
    double currentDeviceScaleFactor = m_state->getDouble(PageAgentState::pageAgentDeviceScaleFactorOverride, 1);
    bool currentEmulateViewport = m_state->getBoolean(PageAgentState::pageAgentEmulateViewport);
    bool currentFitWindow = m_state->getBoolean(PageAgentState::pageAgentFitWindow);
    double currentFontScaleFactor = m_state->getDouble(PageAgentState::fontScaleFactor, 1);
    bool currentTextAutosizing = m_state->getBoolean(PageAgentState::pageAgentTextAutosizingOverride);

    return width != currentWidth || height != currentHeight || deviceScaleFactor != currentDeviceScaleFactor || emulateViewport != currentEmulateViewport || fitWindow != currentFitWindow || fontScaleFactor != currentFontScaleFactor || textAutosizing != currentTextAutosizing;
}
