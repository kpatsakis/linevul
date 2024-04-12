void LayerTreeCoordinator::sizeDidChange(const WebCore::IntSize& newSize)
{
    if (m_rootLayer->size() == newSize)
        return;

    m_rootLayer->setSize(newSize);

    FloatSize oldSize = m_nonCompositedContentLayer->size();
    m_nonCompositedContentLayer->setSize(newSize);

    if (newSize.width() > oldSize.width()) {
        float height = std::min(static_cast<float>(newSize.height()), oldSize.height());
        m_nonCompositedContentLayer->setNeedsDisplayInRect(FloatRect(oldSize.width(), 0, newSize.width() - oldSize.width(), height));
    }

    if (newSize.height() > oldSize.height())
        m_nonCompositedContentLayer->setNeedsDisplayInRect(FloatRect(0, oldSize.height(), newSize.width(), newSize.height() - oldSize.height()));

    if (m_pageOverlayLayer)
        m_pageOverlayLayer->setSize(newSize);

    scheduleLayerFlush();
}
