void LayerWebKitThread::setSublayers(const Vector<RefPtr<LayerWebKitThread> >& sublayers)
{
    if (sublayers == m_sublayers)
        return;

    removeAllSublayers();
    size_t listSize = sublayers.size();
    for (size_t i = 0; i < listSize; ++i)
        addSublayer(sublayers[i]);
}
