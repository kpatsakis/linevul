bool InputHandler::executeTextEditCommand(const WTF::String& commandName)
{
    ASSERT(m_webPage->focusedOrMainFrame() && m_webPage->focusedOrMainFrame()->editor());
    Editor* editor = m_webPage->focusedOrMainFrame()->editor();

    return editor->command(commandName).execute();
}
