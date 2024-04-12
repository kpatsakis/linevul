bool LayerTreeCoordinator::flushPendingLayerChanges()
{
    if (m_waitingForUIProcess)
        return false;

    m_shouldSyncFrame = false;
    bool didSync = m_webPage->corePage()->mainFrame()->view()->syncCompositingStateIncludingSubframes();
    m_nonCompositedContentLayer->syncCompositingStateForThisLayerOnly();
    if (m_pageOverlayLayer)
        m_pageOverlayLayer->syncCompositingStateForThisLayerOnly();

    m_rootLayer->syncCompositingStateForThisLayerOnly();

    if (m_shouldSyncRootLayer) {
        m_webPage->send(Messages::LayerTreeCoordinatorProxy::SetRootCompositingLayer(toCoordinatedGraphicsLayer(m_rootLayer.get())->id()));
        m_shouldSyncRootLayer = false;
    }

    if (m_shouldSyncFrame) {
        didSync = true;
        m_webPage->send(Messages::LayerTreeCoordinatorProxy::DidRenderFrame());
        m_waitingForUIProcess = true;
        m_shouldSyncFrame = false;
    }

    if (m_forceRepaintAsyncCallbackID) {
        m_webPage->send(Messages::WebPageProxy::VoidCallback(m_forceRepaintAsyncCallbackID));
        m_forceRepaintAsyncCallbackID = 0;
    }

    return didSync;
}
