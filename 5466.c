void RenderBlockFlow::repaintOverhangingFloats(bool paintAllDescendants)
{
    if (!hasOverhangingFloats())
        return;

    LayoutStateDisabler layoutStateDisabler(*this);
    const FloatingObjectSet& floatingObjectSet = m_floatingObjects->set();
    FloatingObjectSetIterator end = floatingObjectSet.end();
    for (FloatingObjectSetIterator it = floatingObjectSet.begin(); it != end; ++it) {
        FloatingObject* floatingObject = *it;
        if (logicalBottomForFloat(floatingObject) > logicalHeight()
            && !floatingObject->renderer()->hasSelfPaintingLayer()
            && (floatingObject->shouldPaint() || (paintAllDescendants && floatingObject->renderer()->isDescendantOf(this)))) {

            RenderBox* floatingRenderer = floatingObject->renderer();
            if (RuntimeEnabledFeatures::repaintAfterLayoutEnabled())
                floatingRenderer->setShouldDoFullRepaintAfterLayout(true);
            else
                floatingRenderer->repaint();

            floatingRenderer->repaintOverhangingFloats(false);
        }
    }
}
