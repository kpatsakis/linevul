void RenderLayerScrollableArea::paintScrollCorner(GraphicsContext* context, const IntPoint& paintOffset, const IntRect& damageRect)
{
    IntRect absRect = scrollCornerRect();
    absRect.moveBy(paintOffset);
    if (!absRect.intersects(damageRect))
        return;

    if (m_scrollCorner) {
        m_scrollCorner->paintIntoRect(context, paintOffset, absRect);
        return;
    }

    if (!hasOverlayScrollbars())
        context->fillRect(absRect, Color::white);
}
