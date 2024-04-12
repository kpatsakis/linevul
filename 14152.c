LayoutUnit RenderBlock::collapsedMarginBeforeForChild(const RenderBox* child) const
{
    if (!child->isWritingModeRoot())
        return child->collapsedMarginBefore();

    if (child->isHorizontalWritingMode() == isHorizontalWritingMode())
        return child->collapsedMarginAfter();

    return marginBeforeForChild(child);
}
