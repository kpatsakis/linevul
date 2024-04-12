void WebPagePrivate::setCompositorDrawsRootLayer(bool compositorDrawsRootLayer)
{
#if USE(ACCELERATED_COMPOSITING)
    if (m_page->settings()->forceCompositingMode() == compositorDrawsRootLayer)
        return;

    m_page->settings()->setForceCompositingMode(compositorDrawsRootLayer);

    if (!m_mainFrame)
        return;

    if (FrameView* view = m_mainFrame->view())
        view->updateCompositingLayers();
#endif
}
