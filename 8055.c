void InputHandler::notifyClientOfKeyboardVisibilityChange(bool visible, bool triggeredByFocusChange)
{
    if (!isInputModeEnabled() && visible)
        return;

    if (!triggeredByFocusChange && processingChange() && visible)
        return;

    if (!m_delayKeyboardVisibilityChange) {
        m_webPage->showVirtualKeyboard(visible);
        return;
    }

    m_pendingKeyboardVisibilityChange = visible ? Visible : NotVisible;
}
