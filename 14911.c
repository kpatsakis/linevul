void Document::popCurrentScript()
{
    DCHECK(!m_currentScriptStack.isEmpty());
    m_currentScriptStack.removeLast();
}
