LocalFrame* Document::executingFrame()
{
    LocalDOMWindow* window = executingWindow();
    if (!window)
        return 0;
    return window->frame();
}
