int RenderLayerScrollableArea::pageStep(ScrollbarOrientation orientation) const
{
    int length = (orientation == HorizontalScrollbar) ?
        box().pixelSnappedClientWidth() : box().pixelSnappedClientHeight();
    int minPageStep = static_cast<float>(length) * ScrollableArea::minFractionToStepWhenPaging();
    int pageStep = max(minPageStep, length - ScrollableArea::maxOverlapBetweenPages());

    return max(pageStep, 1);
}
