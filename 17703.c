void LayerWebKitThread::setNeedsDisplay()
{
    if (m_tiler)
        m_tiler->setNeedsDisplay();
    setNeedsCommit(); // FIXME: Replace this with a more targeted message for dirty rect handling with plugin content?
}
