LayoutUnit RenderBlock::minLineHeightForReplacedRenderer(bool isFirstLine, LayoutUnit replacedHeight) const
{
    if (!document().inNoQuirksMode() && replacedHeight)
        return replacedHeight;

    if (!(style(isFirstLine)->lineBoxContain() & LineBoxContainBlock))
        return 0;

    return std::max<LayoutUnit>(replacedHeight, lineHeight(isFirstLine, isHorizontalWritingMode() ? HorizontalLine : VerticalLine, PositionOfInteriorLineBoxes));
}
