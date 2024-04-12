bool InspectorController::handleKeyboardEvent(LocalFrame* frame, const PlatformKeyboardEvent& event)
{
    m_overlay->handleKeyboardEvent(event);
    return false;
}
