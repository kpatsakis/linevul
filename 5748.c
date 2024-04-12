bool RenderLayerScrollableArea::shouldPlaceVerticalScrollbarOnLeft() const
{
    return box().style()->shouldPlaceBlockDirectionScrollbarOnLogicalLeft();
}
