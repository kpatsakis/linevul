void CCLayerTreeHost::clearPendingUpdate()
{
    for (size_t surfaceIndex = 0; surfaceIndex < m_updateList.size(); ++surfaceIndex) {
        LayerChromium* layer = m_updateList[surfaceIndex].get();
        ASSERT(layer->renderSurface());
        layer->clearRenderSurface();
    }
    m_updateList.clear();
}
