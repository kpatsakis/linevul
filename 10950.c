void LayerWebKitThread::setFrame(const FloatRect& rect)
{
    if (rect == m_frame)
      return;

    m_frame = rect;
    setNeedsDisplay();
}
