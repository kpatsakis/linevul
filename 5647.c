PassRefPtr<Scrollbar> Scrollbar::createNativeScrollbar(ScrollableArea* scrollableArea, ScrollbarOrientation orientation, ScrollbarControlSize size)
{
    return adoptRef(new Scrollbar(scrollableArea, orientation, size));
}
