void RenderBlock::adjustForColumns(LayoutSize& offset, const LayoutPoint& point) const
{
    if (!hasColumns())
        return;

    ColumnInfo* colInfo = columnInfo();

    LayoutUnit logicalLeft = logicalLeftOffsetForContent();
    unsigned colCount = columnCount(colInfo);
    LayoutUnit colLogicalWidth = colInfo->desiredColumnWidth();
    LayoutUnit colLogicalHeight = colInfo->columnHeight();

    for (unsigned i = 0; i < colCount; ++i) {
        LayoutRect sliceRect = LayoutRect(logicalLeft, borderBefore() + paddingBefore() + i * colLogicalHeight, colLogicalWidth, colLogicalHeight);
        if (!isHorizontalWritingMode())
            sliceRect = sliceRect.transposedRect();

        LayoutUnit logicalOffset = i * colLogicalHeight;

        if (isHorizontalWritingMode()) {
            if (point.y() >= sliceRect.y() && point.y() < sliceRect.maxY()) {
                if (colInfo->progressionAxis() == ColumnInfo::InlineAxis)
                    offset.expand(columnRectAt(colInfo, i).x() - logicalLeft, -logicalOffset);
                else
                    offset.expand(0, columnRectAt(colInfo, i).y() - logicalOffset - borderBefore() - paddingBefore());
                return;
            }
        } else {
            if (point.x() >= sliceRect.x() && point.x() < sliceRect.maxX()) {
                if (colInfo->progressionAxis() == ColumnInfo::InlineAxis)
                    offset.expand(-logicalOffset, columnRectAt(colInfo, i).y() - logicalLeft);
                else
                    offset.expand(columnRectAt(colInfo, i).x() - logicalOffset - borderBefore() - paddingBefore(), 0);
                return;
            }
        }
    }
}
