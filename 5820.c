void RenderBlockFlow::layoutBlockChild(RenderBox* child, MarginInfo& marginInfo, LayoutUnit& previousFloatLogicalBottom)
{
    LayoutUnit oldPosMarginBefore = maxPositiveMarginBefore();
    LayoutUnit oldNegMarginBefore = maxNegativeMarginBefore();

    child->computeAndSetBlockDirectionMargins(this);

    LayoutUnit estimateWithoutPagination;
    LayoutUnit logicalTopEstimate = estimateLogicalTopPosition(child, marginInfo, estimateWithoutPagination);

    LayoutRect oldRect = child->frameRect();
    LayoutUnit oldLogicalTop = logicalTopForChild(child);

#if !ASSERT_DISABLED
    LayoutSize oldLayoutDelta = RuntimeEnabledFeatures::repaintAfterLayoutEnabled() ? LayoutSize() : view()->layoutDelta();
#endif
    setLogicalTopForChild(child, logicalTopEstimate, ApplyLayoutDelta);

    RenderBlock* childRenderBlock = child->isRenderBlock() ? toRenderBlock(child) : 0;
    RenderBlockFlow* childRenderBlockFlow = (childRenderBlock && child->isRenderBlockFlow()) ? toRenderBlockFlow(child) : 0;
    bool markDescendantsWithFloats = false;
    if (logicalTopEstimate != oldLogicalTop && !child->avoidsFloats() && childRenderBlock && childRenderBlock->containsFloats()) {
        markDescendantsWithFloats = true;
    } else if (UNLIKELY(logicalTopEstimate.mightBeSaturated())) {
        markDescendantsWithFloats = true;
    } else if (!child->avoidsFloats() || child->shrinkToAvoidFloats()) {
        LayoutUnit fb = max(previousFloatLogicalBottom, lowestFloatLogicalBottom());
        if (fb > logicalTopEstimate)
            markDescendantsWithFloats = true;
    }

    if (childRenderBlockFlow) {
        if (markDescendantsWithFloats)
            childRenderBlockFlow->markAllDescendantsWithFloatsForLayout();
        if (!child->isWritingModeRoot())
            previousFloatLogicalBottom = max(previousFloatLogicalBottom, oldLogicalTop + childRenderBlockFlow->lowestFloatLogicalBottom());
    }

    SubtreeLayoutScope layoutScope(*child);
    if (!child->needsLayout())
        child->markForPaginationRelayoutIfNeeded(layoutScope);

    bool childHadLayout = child->everHadLayout();
    bool childNeededLayout = child->needsLayout();
    if (childNeededLayout)
        child->layout();

    bool atBeforeSideOfBlock = marginInfo.atBeforeSideOfBlock();
    bool childIsSelfCollapsing = child->isSelfCollapsingBlock();

    LayoutUnit logicalTopBeforeClear = collapseMargins(child, marginInfo, childIsSelfCollapsing);

    LayoutUnit logicalTopAfterClear = clearFloatsIfNeeded(child, marginInfo, oldPosMarginBefore, oldNegMarginBefore, logicalTopBeforeClear, childIsSelfCollapsing);

    bool paginated = view()->layoutState()->isPaginated();
    if (paginated) {
        logicalTopAfterClear = adjustBlockChildForPagination(logicalTopAfterClear, estimateWithoutPagination, child,
            atBeforeSideOfBlock && logicalTopBeforeClear == logicalTopAfterClear);
    }

    setLogicalTopForChild(child, logicalTopAfterClear, ApplyLayoutDelta);

    if (logicalTopAfterClear != logicalTopEstimate || child->needsLayout() || (paginated && childRenderBlock && childRenderBlock->shouldBreakAtLineToAvoidWidow())) {
        SubtreeLayoutScope layoutScope(*child);
        if (child->shrinkToAvoidFloats()) {
            layoutScope.setChildNeedsLayout(child);
        }

        if (childRenderBlock) {
            if (!child->avoidsFloats() && childRenderBlock->containsFloats())
                childRenderBlockFlow->markAllDescendantsWithFloatsForLayout();
            if (!child->needsLayout())
                child->markForPaginationRelayoutIfNeeded(layoutScope);
        }

        child->layoutIfNeeded();
    }

    if (!marginInfo.canCollapseMarginAfterWithLastChild() && !childIsSelfCollapsing)
        marginInfo.setCanCollapseMarginAfterWithLastChild(true);

    if (marginInfo.atBeforeSideOfBlock() && !childIsSelfCollapsing)
        marginInfo.setAtBeforeSideOfBlock(false);

    determineLogicalLeftPositionForChild(child, ApplyLayoutDelta);

    LayoutSize childOffset = child->location() - oldRect.location();

    setLogicalHeight(logicalHeight() + logicalHeightForChild(child));
    if (mustSeparateMarginAfterForChild(child)) {
        setLogicalHeight(logicalHeight() + marginAfterForChild(child));
        marginInfo.clearMargin();
    }
    if (childRenderBlockFlow)
        addOverhangingFloats(childRenderBlockFlow, !childNeededLayout);

    if (childOffset.width() || childOffset.height()) {
        if (!RuntimeEnabledFeatures::repaintAfterLayoutEnabled())
            view()->addLayoutDelta(childOffset);

        if (RuntimeEnabledFeatures::repaintAfterLayoutEnabled() && childHadLayout && !selfNeedsLayout())
            child->repaintOverhangingFloats(true);
        else if (childHadLayout && !selfNeedsLayout() && child->checkForRepaintDuringLayout())
            child->repaintDuringLayoutIfMoved(oldRect);
    }

    if (!childHadLayout && child->checkForRepaint()) {
        if (!RuntimeEnabledFeatures::repaintAfterLayoutEnabled())
            child->repaint();
        child->repaintOverhangingFloats(true);
    }

    if (paginated) {
        LayoutUnit newHeight = applyAfterBreak(child, logicalHeight(), marginInfo);
        if (newHeight != height())
            setLogicalHeight(newHeight);
    }

    if (!RuntimeEnabledFeatures::repaintAfterLayoutEnabled()) {
        ASSERT(view()->layoutDeltaMatches(oldLayoutDelta));
    }
}
