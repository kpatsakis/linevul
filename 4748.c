void Document::didRemoveText(Node* text, unsigned offset, unsigned length)
{
    if (!m_ranges.isEmpty()) {
        HashSet<Range*>::const_iterator end = m_ranges.end();
        for (HashSet<Range*>::const_iterator it = m_ranges.begin(); it != end; ++it)
            (*it)->didRemoveText(text, offset, length);
    }

    m_markers->removeMarkers(text, offset, length);
    m_markers->shiftMarkers(text, offset + length, 0 - length);
}
