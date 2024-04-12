void LayerWebKitThread::updateTextureContents(double scale)
{
    if (m_contentsScale != scale) {
        m_contentsScale = scale;

        if (drawsContent())
            setNeedsDisplay();
    }

    updateTextureContentsIfNeeded();

    if (includeVisibility()) {
        RenderLayer* renderLayer(static_cast<RenderLayerBacking*>(m_owner->client())->owningLayer());
        bool isVisible(renderLayer->hasVisibleContent() || renderLayer->hasVisibleDescendant());
        if (m_isVisible != isVisible) {
            m_isVisible = isVisible;
            setNeedsCommit();
        }
    }

    size_t listSize = m_sublayers.size();
    for (size_t i = 0; i < listSize; ++i)
        m_sublayers[i]->updateTextureContents(scale);

    listSize = m_overlays.size();
    for (size_t i = 0; i < listSize; ++i)
        m_overlays[i]->updateTextureContents(scale);

    if (maskLayer())
        maskLayer()->updateTextureContents(scale);

    if (replicaLayer())
        replicaLayer()->updateTextureContents(scale);
}
