void RenderBlock::addOverflowFromChildren()
{
    if (!hasColumns()) {
        if (childrenInline())
            toRenderBlockFlow(this)->addOverflowFromInlineChildren();
        else
            addOverflowFromBlockChildren();
    } else {
        ColumnInfo* colInfo = columnInfo();
        if (columnCount(colInfo)) {
            LayoutRect lastRect = columnRectAt(colInfo, columnCount(colInfo) - 1);
            addLayoutOverflow(lastRect);
            addContentsVisualOverflow(lastRect);
        }
    }
}
