LayerTreeCoordinator::~LayerTreeCoordinator()
{
    HashSet<WebCore::CoordinatedGraphicsLayer*> registeredLayers;
    registeredLayers.swap(m_registeredLayers);

    HashSet<WebCore::CoordinatedGraphicsLayer*>::iterator end = registeredLayers.end();
    for (HashSet<WebCore::CoordinatedGraphicsLayer*>::iterator it = registeredLayers.begin(); it != end; ++it)
        (*it)->setCoordinatedGraphicsLayerClient(0);
}
