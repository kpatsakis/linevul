bool RenderBox::scroll(ScrollDirection direction, ScrollGranularity granularity, float delta)
{
    DisableCompositingQueryAsserts disabler;

    ASSERT(!isLogical(direction));

    if (!layer() || !layer()->scrollableArea())
        return false;

    return layer()->scrollableArea()->scroll(direction, granularity, delta);
}
