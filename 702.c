bool Document::allowInlineEventHandlers(Node* node, EventListener* listener, const String& contextURL, const WTF::OrdinalNumber& contextLine)
{
    if (!ContentSecurityPolicy::shouldBypassMainWorld(this) && !contentSecurityPolicy()->allowInlineEventHandlers(contextURL, contextLine))
        return false;

    LocalFrame* frame = executingFrame();
    if (!frame)
        return false;
    if (!frame->script().canExecuteScripts(NotAboutToExecuteScript))
        return false;
    if (node && node->document() != this && !node->document().allowInlineEventHandlers(node, listener, contextURL, contextLine))
        return false;

    return true;
}
