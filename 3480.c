void FrameLoader::loadInSameDocument(const KURL& url, PassRefPtr<SerializedScriptValue> stateObject, FrameLoadType frameLoadType, HistoryLoadType historyLoadType, ClientRedirectPolicy clientRedirect, Document* initiatingDocument)
{
    ASSERT(!stateObject || frameLoadType == FrameLoadTypeBackForward);

    detachDocumentLoader(m_provisionalDocumentLoader);
    if (!m_frame->host())
        return;
    TemporaryChange<FrameLoadType> loadTypeChange(m_loadType, frameLoadType);
    saveScrollState();

    KURL oldURL = m_frame->document()->url();
    bool hashChange = equalIgnoringFragmentIdentifier(url, oldURL) && url.fragmentIdentifier() != oldURL.fragmentIdentifier();
    if (hashChange) {
        m_frame->eventHandler().stopAutoscroll();
        m_frame->localDOMWindow()->enqueueHashchangeEvent(oldURL, url);
    }
    m_documentLoader->setIsClientRedirect(clientRedirect == ClientRedirectPolicy::ClientRedirect);
    updateForSameDocumentNavigation(url, SameDocumentNavigationDefault, nullptr, ScrollRestorationAuto, frameLoadType, initiatingDocument);

    m_documentLoader->initialScrollState().wasScrolledByUser = false;

    checkCompleted();

    m_frame->localDOMWindow()->statePopped(stateObject ? stateObject : SerializedScriptValue::nullValue());

    if (historyLoadType == HistorySameDocumentLoad)
        restoreScrollPositionAndViewState();

    processFragment(url, NavigationWithinSameDocument);
    takeObjectSnapshot();
}
