void InspectorResourceAgent::frameScheduledNavigation(Frame* frame, double)
{
    RefPtr<TypeBuilder::Network::Initiator> initiator = buildInitiatorObject(frame->document(), FetchInitiatorInfo());
    m_frameNavigationInitiatorMap.set(m_pageAgent->frameId(frame), initiator);
}
