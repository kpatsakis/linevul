void RenderBox::computeLogicalWidth(LogicalExtentComputedValues& computedValues) const
{
    computedValues.m_extent = logicalWidth();
    computedValues.m_position = logicalLeft();
    computedValues.m_margins.m_start = marginStart();
    computedValues.m_margins.m_end = marginEnd();

    if (isOutOfFlowPositioned()) {
        computePositionedLogicalWidth(computedValues);
        return;
    }

    if (node() && view()->frameView() && view()->frameView()->layoutRoot(true) == this)
        return;

    if (hasOverrideWidth() && (style()->borderFit() == BorderFitLines || parent()->isFlexibleBoxIncludingDeprecated())) {
        computedValues.m_extent = overrideLogicalContentWidth() + borderAndPaddingLogicalWidth();
        return;
    }

    bool inVerticalBox = parent()->isDeprecatedFlexibleBox() && (parent()->style()->boxOrient() == VERTICAL);
    bool stretching = (parent()->style()->boxAlign() == BSTRETCH);
    bool treatAsReplaced = shouldComputeSizeAsReplaced() && (!inVerticalBox || !stretching);

    RenderStyle* styleToUse = style();
    Length logicalWidthLength = treatAsReplaced ? Length(computeReplacedLogicalWidth(), Fixed) : styleToUse->logicalWidth();

    RenderBlock* cb = containingBlock();
    LayoutUnit containerLogicalWidth = max<LayoutUnit>(0, containingBlockLogicalWidthForContent());
    bool hasPerpendicularContainingBlock = cb->isHorizontalWritingMode() != isHorizontalWritingMode();

    if (isInline() && !isInlineBlockOrInlineTable()) {
        computedValues.m_margins.m_start = minimumValueForLength(styleToUse->marginStart(), containerLogicalWidth);
        computedValues.m_margins.m_end = minimumValueForLength(styleToUse->marginEnd(), containerLogicalWidth);
        if (treatAsReplaced)
            computedValues.m_extent = max<LayoutUnit>(floatValueForLength(logicalWidthLength, 0) + borderAndPaddingLogicalWidth(), minPreferredLogicalWidth());
        return;
    }

    if (treatAsReplaced)
        computedValues.m_extent = logicalWidthLength.value() + borderAndPaddingLogicalWidth();
    else {
        LayoutUnit containerWidthInInlineDirection = containerLogicalWidth;
        if (hasPerpendicularContainingBlock)
            containerWidthInInlineDirection = perpendicularContainingBlockLogicalHeight();
        LayoutUnit preferredWidth = computeLogicalWidthUsing(MainOrPreferredSize, styleToUse->logicalWidth(), containerWidthInInlineDirection, cb);
        computedValues.m_extent = constrainLogicalWidthByMinMax(preferredWidth, containerWidthInInlineDirection, cb);
    }

    if (hasPerpendicularContainingBlock || isFloating() || isInline()) {
        computedValues.m_margins.m_start = minimumValueForLength(styleToUse->marginStart(), containerLogicalWidth);
        computedValues.m_margins.m_end = minimumValueForLength(styleToUse->marginEnd(), containerLogicalWidth);
    } else {
        bool hasInvertedDirection = cb->style()->isLeftToRightDirection() != style()->isLeftToRightDirection();
        computeInlineDirectionMargins(cb, containerLogicalWidth, computedValues.m_extent,
            hasInvertedDirection ? computedValues.m_margins.m_end : computedValues.m_margins.m_start,
            hasInvertedDirection ? computedValues.m_margins.m_start : computedValues.m_margins.m_end);
    }

    if (!hasPerpendicularContainingBlock && containerLogicalWidth && containerLogicalWidth != (computedValues.m_extent + computedValues.m_margins.m_start + computedValues.m_margins.m_end)
        && !isFloating() && !isInline() && !cb->isFlexibleBoxIncludingDeprecated() && !cb->isRenderGrid()) {
        LayoutUnit newMargin = containerLogicalWidth - computedValues.m_extent - cb->marginStartForChild(this);
        bool hasInvertedDirection = cb->style()->isLeftToRightDirection() != style()->isLeftToRightDirection();
        if (hasInvertedDirection)
            computedValues.m_margins.m_start = newMargin;
        else
            computedValues.m_margins.m_end = newMargin;
    }

    if (styleToUse->textAutosizingMultiplier() != 1 && styleToUse->marginStart().type() == Fixed) {
        Node* parentNode = generatingNode();
        if (parentNode && (isHTMLOListElement(*parentNode) || isHTMLUListElement(*parentNode))) {
            const float adjustedMargin = (1 - 1.0 / styleToUse->textAutosizingMultiplier()) * getMaxWidthListMarker(this);
            bool hasInvertedDirection = cb->style()->isLeftToRightDirection() != style()->isLeftToRightDirection();
            if (hasInvertedDirection)
                computedValues.m_margins.m_end += adjustedMargin;
            else
                computedValues.m_margins.m_start += adjustedMargin;
        }
    }
}
