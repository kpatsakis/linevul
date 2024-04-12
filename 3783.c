IntRect RenderLayerScrollableArea::scrollCornerRect() const
{
    bool hasHorizontalBar = horizontalScrollbar();
    bool hasVerticalBar = verticalScrollbar();
    bool hasResizer = box().style()->resize() != RESIZE_NONE;
    if ((hasHorizontalBar && hasVerticalBar) || (hasResizer && (hasHorizontalBar || hasVerticalBar)))
        return cornerRect(box().style(), horizontalScrollbar(), verticalScrollbar(), box().pixelSnappedBorderBoxRect());
    return IntRect();
}
