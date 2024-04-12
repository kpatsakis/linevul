void RenderBlockFlow::paintFloats(PaintInfo& paintInfo, const LayoutPoint& paintOffset, bool preservePhase)
{
    if (!m_floatingObjects)
        return;

    const FloatingObjectSet& floatingObjectSet = m_floatingObjects->set();
    FloatingObjectSetIterator end = floatingObjectSet.end();
    for (FloatingObjectSetIterator it = floatingObjectSet.begin(); it != end; ++it) {
        FloatingObject* floatingObject = *it;
        if (floatingObject->shouldPaint() && !floatingObject->renderer()->hasSelfPaintingLayer()) {
            PaintInfo currentPaintInfo(paintInfo);
            currentPaintInfo.phase = preservePhase ? paintInfo.phase : PaintPhaseBlockBackground;
            LayoutPoint childPoint = flipFloatForWritingModeForChild(floatingObject, LayoutPoint(paintOffset.x() + xPositionForFloatIncludingMargin(floatingObject) - floatingObject->renderer()->x(), paintOffset.y() + yPositionForFloatIncludingMargin(floatingObject) - floatingObject->renderer()->y()));
            floatingObject->renderer()->paint(currentPaintInfo, childPoint);
            if (!preservePhase) {
                currentPaintInfo.phase = PaintPhaseChildBlockBackgrounds;
                floatingObject->renderer()->paint(currentPaintInfo, childPoint);
                currentPaintInfo.phase = PaintPhaseFloat;
                floatingObject->renderer()->paint(currentPaintInfo, childPoint);
                currentPaintInfo.phase = PaintPhaseForeground;
                floatingObject->renderer()->paint(currentPaintInfo, childPoint);
                currentPaintInfo.phase = PaintPhaseOutline;
                floatingObject->renderer()->paint(currentPaintInfo, childPoint);
            }
        }
    }
}
