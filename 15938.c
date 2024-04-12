void CCLayerTreeHost::setViewport(const IntSize& viewportSize)
{
    m_viewportSize = viewportSize;
    setNeedsCommitThenRedraw();
}
