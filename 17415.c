void InputHandler::cancelSelection()
{
    if (!isActiveTextEdit())
        return;

    ASSERT(m_currentFocusElement->document() && m_currentFocusElement->document()->frame());

    int selectionStartPosition = selectionStart();
    ProcessingChangeGuard guard(this);
    setCursorPosition(selectionStartPosition);
}
