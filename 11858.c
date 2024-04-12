void HTMLBodyElement::setScrollTop(int scrollTop)
{
    Document& document = this->document();
    document.updateLayoutIgnorePendingStylesheets();

    if (RuntimeEnabledFeatures::scrollTopLeftInteropEnabled()) {
        RenderBox* render = renderBox();
        if (!render)
            return;
        if (render->hasOverflowClip()) {
            render->setScrollTop(static_cast<int>(scrollTop * render->style()->effectiveZoom()));
            return;
        }
        if (!document.inQuirksMode())
            return;
    }

    LocalFrame* frame = document.frame();
    if (!frame)
        return;
    FrameView* view = frame->view();
    if (!view)
        return;
    view->setScrollPosition(IntPoint(view->scrollX(), static_cast<int>(scrollTop * frame->pageZoomFactor())));
}
