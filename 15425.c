void Document::didInsertText(Node* text, unsigned offset, unsigned length)
{
    for (Range* range : m_ranges)
        range->didInsertText(text, offset, length);

    m_markers->shiftMarkers(text, offset, length);
}
