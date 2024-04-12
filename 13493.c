LayoutUnit RenderBox::computeReplacedLogicalWidthRespectingMinMaxWidth(LayoutUnit logicalWidth, ShouldComputePreferred shouldComputePreferred) const
{
    LayoutUnit minLogicalWidth = (shouldComputePreferred == ComputePreferred && style()->logicalMinWidth().isPercent()) || style()->logicalMinWidth().isUndefined() ? logicalWidth : computeReplacedLogicalWidthUsing(style()->logicalMinWidth());
    LayoutUnit maxLogicalWidth = (shouldComputePreferred == ComputePreferred && style()->logicalMaxWidth().isPercent()) || style()->logicalMaxWidth().isUndefined() ? logicalWidth : computeReplacedLogicalWidthUsing(style()->logicalMaxWidth());
    return max(minLogicalWidth, min(logicalWidth, maxLogicalWidth));
}
