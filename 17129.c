void WebPagePrivate::clearFocusNode()
{
    Frame* frame = focusedOrMainFrame();
    if (!frame)
        return;
    ASSERT(frame->document());

    if (frame->document()->focusedNode())
        frame->page()->focusController()->setFocusedNode(0, frame);
}
