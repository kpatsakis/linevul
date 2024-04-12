void RenderBox::paintRootBoxFillLayers(const PaintInfo& paintInfo)
{
    if (paintInfo.skipRootBackground())
        return;

    RenderObject* rootBackgroundRenderer = rendererForRootBackground();

    const FillLayer* bgLayer = rootBackgroundRenderer->style()->backgroundLayers();
    Color bgColor = rootBackgroundRenderer->resolveColor(CSSPropertyBackgroundColor);

    paintFillLayers(paintInfo, bgColor, bgLayer, view()->backgroundRect(this), BackgroundBleedNone, CompositeSourceOver, rootBackgroundRenderer);
}
