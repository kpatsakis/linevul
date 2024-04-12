void InputHandler::removeAttributedTextMarker()
{
    if (m_currentFocusElement && m_currentFocusElement->document())
        m_currentFocusElement->document()->markers()->removeMarkers(DocumentMarker::AttributeText);

    m_composingTextStart = 0;
    m_composingTextEnd = 0;
}
