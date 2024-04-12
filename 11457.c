void InspectorController::didCommitLoadForMainFrame()
{
    Vector<InspectorAgent*> agents = m_moduleAgents;
    for (size_t i = 0; i < agents.size(); i++)
        agents[i]->didCommitLoadForMainFrame();
}
