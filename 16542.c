void InspectorPageAgent::frameStartedLoading(Frame* frame)
{
    m_frontend->frameStartedLoading(frameId(frame));
}
