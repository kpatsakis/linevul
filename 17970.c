void webkit_web_frame_layout(WebKitWebFrame* frame)
{
    Frame* coreFrame = core(frame);
    if (!coreFrame)
        return;

    FrameView* view = coreFrame->view();
    if (!view)
        return;

    view->layout();
}
