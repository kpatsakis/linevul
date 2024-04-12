LayoutUnit RenderBlock::logicalRightSelectionOffset(RenderBlock* rootBlock, LayoutUnit position)
{
    if (rootBlock != this)
        return containingBlock()->logicalRightSelectionOffset(rootBlock, position + logicalTop());
    return logicalRightOffsetForContent();
}
