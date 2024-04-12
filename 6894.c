LayoutUnit RenderBlockFlow::adjustLogicalRightOffsetForLine(LayoutUnit offsetFromFloats, bool applyTextIndent) const
{
    LayoutUnit right = offsetFromFloats;

    if (applyTextIndent && !style()->isLeftToRightDirection())
        right -= textIndentOffset();

    return right;
}
