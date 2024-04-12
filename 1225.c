static Editor::Command command(Document* document, const String& commandName, bool userInterface = false)
{
    Frame* frame = document->frame();
    if (!frame || frame->document() != document)
        return Editor::Command();

    document->updateStyleIfNeeded();

    return frame->editor()->command(commandName,
        userInterface ? CommandFromDOMWithUserInterface : CommandFromDOM);
}
