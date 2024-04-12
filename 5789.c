void RenderBlock::adjustStartEdgeForWritingModeIncludingColumns(LayoutRect& rect) const
{
    ASSERT(hasColumns());
    if (!hasColumns() || !style()->isFlippedBlocksWritingMode())
        return;

    ColumnInfo* colInfo = columnInfo();
    LayoutUnit columnLogicalHeight = colInfo->columnHeight();
    LayoutUnit expandedLogicalHeight = borderBefore() + paddingBefore() + columnCount(colInfo) * columnLogicalHeight + borderAfter() + paddingAfter() + scrollbarLogicalHeight();

    if (isHorizontalWritingMode())
        rect.setY(expandedLogicalHeight - rect.maxY());
    else
        rect.setX(expandedLogicalHeight - rect.maxX());
}
