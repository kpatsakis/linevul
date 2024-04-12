void Document::webkitDidEnterFullScreenForElement(Element*)
{
    if (!m_fullScreenElement)
        return;

    if (!attached() || inPageCache())
        return;

    m_fullScreenElement->didBecomeFullscreenElement();

    m_fullScreenChangeDelayTimer.startOneShot(0);
}
