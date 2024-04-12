void FrameLoader::didExplicitOpen()
{
    if (!m_stateMachine.committedFirstRealDocumentLoad())
        m_stateMachine.advanceTo(FrameLoaderStateMachine::CommittedFirstRealLoad);

    if (Frame* parent = m_frame->tree().parent()) {
        if ((parent->isLocalFrame() && toLocalFrame(parent)->document()->loadEventStillNeeded())
            || (parent->isRemoteFrame() && parent->isLoading())) {
            m_progressTracker->progressStarted();
        }
    }

    m_frame->navigationScheduler().cancel();
}
