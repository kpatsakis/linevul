void HTMLBodyElement::setScrollLeft(int scrollLeft)
{
    Document& document = this->document();
    document.updateLayoutIgnorePendingStylesheets();

    if (RuntimeEnabledFeatures::scrollTopLeftInteropEnabled()) {
        RenderBox* render = renderBox();
        if (!render)
            return;
        if (render->hasOverflowClip()) {
            render->setScrollLeft(static_cast<int>(scrollLeft * render->style()->effectiveZoom()));
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
    view->setScrollPosition(IntPoint(static_cast<int>(scrollLeft * frame->pageZoomFactor()), view->scrollY()));
}
