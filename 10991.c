void InspectorPageAgent::domContentLoadedEventFired(Frame* frame)
{
    if (!frame->isMainFrame())
        return;
    m_frontend->domContentEventFired(currentTime());
}
