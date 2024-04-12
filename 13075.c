bool RenderBox::hasRelativeLogicalHeight() const
{
    return style()->logicalHeight().isPercent()
        || style()->logicalMinHeight().isPercent()
        || style()->logicalMaxHeight().isPercent();
}
