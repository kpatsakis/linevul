void InspectorPageAgent::didClearWindowObjectInWorld(Frame* frame, DOMWrapperWorld* world)
{
    if (world != mainThreadNormalWorld())
        return;

    if (frame == m_page->mainFrame())
        m_injectedScriptManager->discardInjectedScripts();

    if (!m_frontend)
        return;

    RefPtr<JSONObject> scripts = m_state->getObject(PageAgentState::pageAgentScriptsToEvaluateOnLoad);
    if (scripts) {
        JSONObject::const_iterator end = scripts->end();
        for (JSONObject::const_iterator it = scripts->begin(); it != end; ++it) {
            String scriptText;
            if (it->value->asString(&scriptText))
                frame->script().executeScriptInMainWorld(scriptText);
        }
    }
    if (!m_scriptToEvaluateOnLoadOnce.isEmpty())
        frame->script().executeScriptInMainWorld(m_scriptToEvaluateOnLoadOnce);
}
