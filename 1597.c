IntSize FrameView::scrollOffsetForFixedPosition() const
{
    return toIntSize(clampScrollPosition(scrollPosition()));
}
