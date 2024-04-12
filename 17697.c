LayoutUnit RenderBox::computeContentAndScrollbarLogicalHeightUsing(const Length& height, LayoutUnit intrinsicContentHeight) const
{
    if (height.isIntrinsic()) {
        if (intrinsicContentHeight == -1)
            return -1; // Intrinsic height isn't available.
        return computeIntrinsicLogicalContentHeightUsing(height, intrinsicContentHeight, borderAndPaddingLogicalHeight());
    }
    if (height.isFixed())
        return height.value();
    if (height.isPercent())
        return computePercentageLogicalHeight(height);
    return -1;
}
