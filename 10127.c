void LayoutBlockFlow::styleWillChange(StyleDifference diff, const ComputedStyle& newStyle)
{
    const ComputedStyle* oldStyle = style();
    s_canPropagateFloatIntoSibling = oldStyle ? !isFloatingOrOutOfFlowPositioned() && !avoidsFloats() : false;
    if (oldStyle && parent() && diff.needsFullLayout() && oldStyle->position() != newStyle.position()
        && containsFloats() && !isFloating() && !isOutOfFlowPositioned() && newStyle.hasOutOfFlowPosition())
            markAllDescendantsWithFloatsForLayout();

    LayoutBlock::styleWillChange(diff, newStyle);
}
