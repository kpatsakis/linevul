void LayerTreeCoordinator::attachLayer(CoordinatedGraphicsLayer* layer)
{
    ASSERT(!m_registeredLayers.contains(layer));
    m_registeredLayers.add(layer);

    layer->setContentsScale(m_contentsScale);
    layer->adjustVisibleRect();
}
