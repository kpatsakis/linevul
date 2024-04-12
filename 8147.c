void FrameView::addScrollableArea(ScrollableArea* scrollableArea)
{
    ASSERT(scrollableArea);
    if (!m_scrollableAreas)
        m_scrollableAreas = adoptPtr(new ScrollableAreaSet);
    m_scrollableAreas->add(scrollableArea);
}
