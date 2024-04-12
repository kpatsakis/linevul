void InspectorPageAgent::setShowScrollBottleneckRects(ErrorString* errorString, bool show)
{
    m_state->setBoolean(PageAgentState::pageAgentShowScrollBottleneckRects, show);
    if (show && !forceCompositingMode(errorString))
        return;
    m_client->setShowScrollBottleneckRects(show);
}
