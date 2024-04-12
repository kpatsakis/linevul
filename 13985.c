void FrameView::paintScrollbar(GraphicsContext* context, Scrollbar* bar, const IntRect& rect)
{
    bool needsBackgorund = bar->isCustomScrollbar() && m_frame->isMainFrame();
    if (needsBackgorund) {
        IntRect toFill = bar->frameRect();
        toFill.intersect(rect);
        context->fillRect(toFill, baseBackgroundColor());
    }

    ScrollView::paintScrollbar(context, bar, rect);
}
