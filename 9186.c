void InspectorPageAgent::didCommitLoad(Frame*, DocumentLoader* loader)
{
    if (loader->frame() == m_page->mainFrame()) {
        m_scriptToEvaluateOnLoadOnce = m_pendingScriptToEvaluateOnLoadOnce;
        m_scriptPreprocessorSource = m_pendingScriptPreprocessor;
        m_pendingScriptToEvaluateOnLoadOnce = String();
        m_pendingScriptPreprocessor = String();
    }
    m_frontend->frameNavigated(buildObjectForFrame(loader->frame()));
}
