void WebPageProxy::printFrame(uint64_t frameID)
{
    ASSERT(!m_isPerformingDOMPrintOperation);
    m_isPerformingDOMPrintOperation = true;

    WebFrameProxy* frame = process()->webFrame(frameID);
    MESSAGE_CHECK(frame);

    m_uiClient.printFrame(this, frame);

    m_isPerformingDOMPrintOperation = false;
}
