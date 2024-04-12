void InputHandler::nodeTextChanged(const Node* node)
{
    if (processingChange() || !node || node != m_currentFocusElement || m_receivedBackspaceKeyDown)
        return;

    InputLog(LogLevelInfo, "InputHandler::nodeTextChanged");

    m_webPage->m_client->inputTextChanged();

    removeAttributedTextMarker();
}
