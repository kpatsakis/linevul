LayoutRect RenderBlock::logicalLeftSelectionGap(RenderBlock* rootBlock, const LayoutPoint& rootBlockPhysicalPosition, const LayoutSize& offsetFromRootBlock,
                                                RenderObject* selObj, LayoutUnit logicalLeft, LayoutUnit logicalTop, LayoutUnit logicalHeight, const PaintInfo* paintInfo)
{
    LayoutUnit rootBlockLogicalTop = rootBlock->blockDirectionOffset(offsetFromRootBlock) + logicalTop;
    LayoutUnit rootBlockLogicalLeft = max(logicalLeftSelectionOffset(rootBlock, logicalTop), logicalLeftSelectionOffset(rootBlock, logicalTop + logicalHeight));
    LayoutUnit rootBlockLogicalRight = min(rootBlock->inlineDirectionOffset(offsetFromRootBlock) + floorToInt(logicalLeft), min(logicalRightSelectionOffset(rootBlock, logicalTop), logicalRightSelectionOffset(rootBlock, logicalTop + logicalHeight)));
    LayoutUnit rootBlockLogicalWidth = rootBlockLogicalRight - rootBlockLogicalLeft;
    if (rootBlockLogicalWidth <= 0)
        return LayoutRect();

    LayoutRect gapRect = rootBlock->logicalRectToPhysicalRect(rootBlockPhysicalPosition, LayoutRect(rootBlockLogicalLeft, rootBlockLogicalTop, rootBlockLogicalWidth, logicalHeight));
    if (paintInfo)
        paintInfo->context->fillRect(pixelSnappedIntRect(gapRect), selObj->selectionBackgroundColor());
    return gapRect;
}
