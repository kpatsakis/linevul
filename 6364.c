Node* Range::pastLastNode() const
{
    if (!m_start.container() || !m_end.container())
        return 0;
    if (m_end.container()->offsetInCharacters())
        return m_end.container()->traverseNextSibling();
    if (Node* child = m_end.container()->childNode(m_end.offset()))
        return child;
    return m_end.container()->traverseNextSibling();
}
