LayoutUnit RenderBox::viewLogicalHeightForPercentages() const
{
    if (document().printing())
        return static_cast<LayoutUnit>(view()->pageLogicalHeight());
    return view()->viewLogicalHeight();
}
