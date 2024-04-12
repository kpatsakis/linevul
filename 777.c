void InputHandler::clearField()
{
    if (!isActiveTextEdit())
        return;

    ASSERT(m_currentFocusElement->document() && m_currentFocusElement->document()->frame() && m_currentFocusElement->document()->frame()->editor());
    Editor* editor = m_currentFocusElement->document()->frame()->editor();

    editor->command("SelectAll").execute();
    editor->command("DeleteBackward").execute();
}
