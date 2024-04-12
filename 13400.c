void LayerTreeCoordinator::setVisibleContentsRect(const IntRect& rect, float scale, const FloatPoint& trajectoryVector)
{
    bool contentsRectDidChange = rect != m_visibleContentsRect;
    bool contentsScaleDidChange = scale != m_contentsScale;

    toCoordinatedGraphicsLayer(m_nonCompositedContentLayer.get())->setVisibleContentRectTrajectoryVector(trajectoryVector);

    if (contentsRectDidChange || contentsScaleDidChange) {
        m_visibleContentsRect = rect;
        m_contentsScale = scale;

        HashSet<WebCore::CoordinatedGraphicsLayer*>::iterator end = m_registeredLayers.end();
        for (HashSet<WebCore::CoordinatedGraphicsLayer*>::iterator it = m_registeredLayers.begin(); it != end; ++it) {
            if (contentsScaleDidChange)
                (*it)->setContentsScale(scale);
            if (contentsRectDidChange)
                (*it)->adjustVisibleRect();
        }
    }

    scheduleLayerFlush();
    if (m_webPage->useFixedLayout())
        m_webPage->setFixedVisibleContentRect(rect);
    if (contentsRectDidChange)
        m_shouldSendScrollPositionUpdate = true;
}
