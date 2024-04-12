LayoutUnit RenderFlexibleBox::flowAwareBorderAfter() const
{
    switch (transformedWritingMode()) {
    case TopToBottomWritingMode:
        return borderBottom();
    case BottomToTopWritingMode:
        return borderTop();
    case LeftToRightWritingMode:
        return borderRight();
    case RightToLeftWritingMode:
        return borderLeft();
    }
    ASSERT_NOT_REACHED();
    return borderTop();
}
