void LayoutBlockFlow::checkForPaginationLogicalHeightChange(LayoutUnit& pageLogicalHeight, bool& pageLogicalHeightChanged, bool& hasSpecifiedPageLogicalHeight)
{
    if (LayoutMultiColumnFlowThread* flowThread = multiColumnFlowThread()) {
        LayoutUnit columnHeight;
        if (hasDefiniteLogicalHeight() || isLayoutView()) {
            LogicalExtentComputedValues computedValues;
            computeLogicalHeight(LayoutUnit(), logicalTop(), computedValues);
            columnHeight = computedValues.m_extent - borderAndPaddingLogicalHeight() - scrollbarLogicalHeight();
        }
        pageLogicalHeightChanged = columnHeight != flowThread->columnHeightAvailable();
        flowThread->setColumnHeightAvailable(std::max(columnHeight, LayoutUnit()));
    } else if (isLayoutFlowThread()) {
        LayoutFlowThread* flowThread = toLayoutFlowThread(this);

        pageLogicalHeight = flowThread->isPageLogicalHeightKnown() ? LayoutUnit(1) : LayoutUnit();

        pageLogicalHeightChanged = flowThread->pageLogicalSizeChanged();
    }
}
