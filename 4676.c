FrameLoader::FrameLoader(Frame* frame, FrameLoaderClient* client)
    : m_frame(frame)
    , m_client(client)
    , m_policyChecker(frame)
    , m_history(frame)
    , m_notifer(frame)
    , m_state(FrameStateCommittedPage)
    , m_loadType(FrameLoadTypeStandard)
    , m_delegateIsHandlingProvisionalLoadError(false)
    , m_firstLayoutDone(false)
    , m_quickRedirectComing(false)
    , m_sentRedirectNotification(false)
    , m_inStopAllLoaders(false)
    , m_isExecutingJavaScriptFormAction(false)
    , m_didCallImplicitClose(false)
    , m_wasUnloadEventEmitted(false)
    , m_unloadEventBeingDispatched(false)
    , m_isComplete(false)
    , m_isLoadingMainResource(false)
    , m_needsClear(false)
    , m_receivedData(false)
    , m_encodingWasChosenByUser(false)
    , m_containsPlugIns(false)
    , m_checkTimer(this, &FrameLoader::checkTimerFired)
    , m_shouldCallCheckCompleted(false)
    , m_shouldCallCheckLoadComplete(false)
    , m_opener(0)
    , m_creatingInitialEmptyDocument(false)
    , m_isDisplayingInitialEmptyDocument(false)
    , m_committedFirstRealDocumentLoad(false)
    , m_didPerformFirstNavigation(false)
    , m_loadingFromCachedPage(false)
    , m_suppressOpenerInNewFrame(false)
#ifndef NDEBUG
    , m_didDispatchDidCommitLoad(false)
#endif
{
}