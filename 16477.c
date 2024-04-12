void InspectorClientImpl::requestPageScaleFactor(float scale, const IntPoint& origin)
{
    m_inspectedWebView->setPageScaleFactor(scale);
    m_inspectedWebView->setMainFrameScrollOffset(origin);
}
