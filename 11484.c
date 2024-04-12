void InspectorPageAgent::applyEmulatedMedia(String* media)
{
    String emulatedMedia = m_state->getString(PageAgentState::pageAgentEmulatedMedia);
    if (!emulatedMedia.isEmpty())
        *media = emulatedMedia;
}
