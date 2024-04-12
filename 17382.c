bool FrameView::wheelEvent(const PlatformWheelEvent& wheelEvent)
{
    bool allowScrolling = userInputScrollable(HorizontalScrollbar) || userInputScrollable(VerticalScrollbar);

#if !USE(RUBBER_BANDING)
    if (!isScrollable())
        allowScrolling = false;
#endif

    if (allowScrolling && ScrollableArea::handleWheelEvent(wheelEvent))
        return true;

    if (m_frame->settings()->pinchVirtualViewportEnabled() && m_frame->isMainFrame())
        return page()->frameHost().pinchViewport().handleWheelEvent(wheelEvent);

    return false;
}
