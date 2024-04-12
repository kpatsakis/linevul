LayerWebKitThread::~LayerWebKitThread()
{
    if (m_tiler)
        m_tiler->layerWebKitThreadDestroyed();

    ASSERT(!superlayer());

    removeAll(m_sublayers);
    removeAll(m_overlays);
}
