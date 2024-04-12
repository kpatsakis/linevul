void InspectorController::scriptsEnabled(bool  enabled)
{
    if (InspectorPageAgent* pageAgent = m_instrumentingAgents->inspectorPageAgent())
        pageAgent->scriptsEnabled(enabled);
}
