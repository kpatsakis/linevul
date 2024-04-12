void Document::addMessage(MessageSource source, MessageLevel level, const String& message, const String& sourceURL, unsigned lineNumber, PassRefPtr<ScriptCallStack> callStack, ScriptState* state, unsigned long requestIdentifier)
{
    if (!isContextThread()) {
        postTask(AddConsoleMessageTask::create(source, level, message));
        return;
    }

    if (Page* page = this->page())
        page->console()->addMessage(source, level, message, sourceURL, lineNumber, callStack, state, requestIdentifier);
}
