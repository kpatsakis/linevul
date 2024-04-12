LayoutUnit RenderBox::fillAvailableMeasure(LayoutUnit availableLogicalWidth) const
{
    LayoutUnit marginStart = 0;
    LayoutUnit marginEnd = 0;
    return fillAvailableMeasure(availableLogicalWidth, marginStart, marginEnd);
}
