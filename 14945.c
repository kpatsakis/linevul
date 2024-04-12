void QQuickWebViewPrivate::FlickableAxisLocker::reset()
{
    m_allowedDirection = QQuickFlickable::AutoFlickDirection;
    m_sampleCount = 0;
}
