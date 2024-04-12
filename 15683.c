void LayerTreeHostQt::removeTile(WebLayerID layerID, int tileID)
{
    m_webPage->send(Messages::LayerTreeHostProxy::RemoveTileForLayer(layerID, tileID));
}
