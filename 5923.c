void WebPageProxy::close()
{
    if (!isValid())
        return;

    m_isClosed = true;

    m_backForwardList->pageClosed();
    m_pageClient->pageClosed();

    process()->disconnectFramesFromPage(this);
    m_mainFrame = 0;

#if ENABLE(INSPECTOR)
    if (m_inspector) {
        m_inspector->invalidate();
        m_inspector = 0;
    }
#endif

#if ENABLE(FULLSCREEN_API)
    if (m_fullScreenManager) {
        m_fullScreenManager->invalidate();
        m_fullScreenManager = 0;
    }
#endif

    if (m_openPanelResultListener) {
        m_openPanelResultListener->invalidate();
        m_openPanelResultListener = 0;
    }

    m_geolocationPermissionRequestManager.invalidateRequests();

    m_toolTip = String();

    m_mainFrameHasHorizontalScrollbar = false;
    m_mainFrameHasVerticalScrollbar = false;

    m_mainFrameIsPinnedToLeftSide = false;
    m_mainFrameIsPinnedToRightSide = false;

    invalidateCallbackMap(m_voidCallbacks);
    invalidateCallbackMap(m_dataCallbacks);
    invalidateCallbackMap(m_stringCallbacks);
    m_loadDependentStringCallbackIDs.clear();
    invalidateCallbackMap(m_scriptValueCallbacks);
    invalidateCallbackMap(m_computedPagesCallbacks);

    Vector<WebEditCommandProxy*> editCommandVector;
    copyToVector(m_editCommandSet, editCommandVector);
    m_editCommandSet.clear();
    for (size_t i = 0, size = editCommandVector.size(); i < size; ++i)
        editCommandVector[i]->invalidate();

    m_activePopupMenu = 0;

    m_estimatedProgress = 0.0;
    
    m_loaderClient.initialize(0);
    m_policyClient.initialize(0);
    m_uiClient.initialize(0);

    m_drawingArea.clear();

    process()->send(Messages::WebPage::Close(), m_pageID);
    process()->removeWebPage(m_pageID);
}
