LayoutUnit RenderFlexibleBox::flowAwareMarginBeforeForChild(RenderBox* child) const
{
    switch (transformedWritingMode()) {
    case TopToBottomWritingMode:
        return child->marginTop();
    case BottomToTopWritingMode:
        return child->marginBottom();
    case LeftToRightWritingMode:
        return child->marginLeft();
    case RightToLeftWritingMode:
        return child->marginRight();
    }
    ASSERT_NOT_REACHED();
    return marginTop();
}
