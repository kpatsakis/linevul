bool WebPagePrivate::commitRootLayerIfNeeded()
{
#if DEBUG_AC_COMMIT
    Platform::logAlways(Platform::LogLevelCritical,
        "%s: m_suspendRootLayerCommit = %d, m_needsCommit = %d, m_frameLayers = 0x%p, m_frameLayers->hasLayer() = %d, needsLayoutRecursive() = %d",
        WTF_PRETTY_FUNCTION,
        m_suspendRootLayerCommit,
        m_needsCommit,
        m_frameLayers.get(),
        m_frameLayers && m_frameLayers->hasLayer(),
        m_mainFrame && m_mainFrame->view() && needsLayoutRecursive(m_mainFrame->view()));
#endif

    if (m_suspendRootLayerCommit)
        return false;

    if (!m_needsCommit)
        return false;

    if (!(m_frameLayers && m_frameLayers->hasLayer()) && !m_overlayLayer
     && !m_needsOneShotDrawingSynchronization)
        return false;

    FrameView* view = m_mainFrame->view();
    if (!view)
        return false;

    updateDelegatedOverlays();

    if (needsLayoutRecursive(view)) {
        ASSERT(!needsOneShotDrawingSynchronization());
        return false;
    }

    willComposite();
    m_needsCommit = false;
    m_needsOneShotDrawingSynchronization = false;

    if (m_rootLayerCommitTimer->isActive())
        m_rootLayerCommitTimer->stop();

    double scale = currentScale();
    if (m_frameLayers && m_frameLayers->hasLayer())
        m_frameLayers->commitOnWebKitThread(scale);

    if (m_overlayLayer)
        m_overlayLayer->platformLayer()->commitOnWebKitThread(scale);

    IntRect layoutRect(scrollPosition(), actualVisibleSize());
    IntRect documentRect(view->minimumScrollPosition(), view->contentsSize());
    bool drawsRootLayer = compositorDrawsRootLayer();

    Platform::userInterfaceThreadMessageClient()->dispatchSyncMessage(
        Platform::createMethodCallMessage(
            &WebPagePrivate::commitRootLayer,
            this,
            layoutRect,
            documentRect,
            drawsRootLayer));

    didComposite();
    return true;
}
