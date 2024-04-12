void InspectorOverlay::reset(const IntSize& viewportSize, const IntSize& frameViewFullSize, int scrollX, int scrollY)
{
    RefPtr<JSONObject> resetData = JSONObject::create();
    resetData->setNumber("pageScaleFactor", m_page->pageScaleFactor());
    resetData->setNumber("deviceScaleFactor", m_page->deviceScaleFactor());
    resetData->setObject("viewportSize", buildObjectForSize(viewportSize));
    resetData->setObject("frameViewFullSize", buildObjectForSize(frameViewFullSize));
    resetData->setNumber("pageZoomFactor", m_page->mainFrame()->pageZoomFactor());
    resetData->setNumber("scrollX", scrollX);
    resetData->setNumber("scrollY", scrollY);
    evaluateInOverlay("reset", resetData.release());
}
