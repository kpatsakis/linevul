bool LayoutBlockFlow::mustSeparateMarginBeforeForChild(const LayoutBox& child) const
{
    ASSERT(!child.selfNeedsLayout());
    const ComputedStyle& childStyle = child.styleRef();
    if (!child.isWritingModeRoot())
        return childStyle.marginBeforeCollapse() == MSEPARATE;
    if (child.isHorizontalWritingMode() == isHorizontalWritingMode())
        return childStyle.marginAfterCollapse() == MSEPARATE;

    return false;
}
