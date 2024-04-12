void InspectorPageAgent::setScriptExecutionDisabled(ErrorString*, bool value)
{
    m_state->setBoolean(PageAgentState::pageAgentScriptExecutionDisabled, value);
    if (!mainFrame())
        return;

    Settings* settings = mainFrame()->settings();
    if (settings) {
        m_ignoreScriptsEnabledNotification = true;
        settings->setScriptEnabled(!value);
        m_ignoreScriptsEnabledNotification = false;
    }
}
