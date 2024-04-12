void FrameLoader::loadInSameDocument(const KURL& url, SerializedScriptValue* stateObject, bool isNewNavigation)
{
    ASSERT(!stateObject || (stateObject && !isNewNavigation));

    m_frame->document()->setURL(url);
    documentLoader()->replaceRequestURLForSameDocumentNavigation(url);
    if (isNewNavigation && !shouldTreatURLAsSameAsCurrent(url) && !stateObject) {
        

        history()->updateBackForwardListForFragmentScroll();
    }
    
    String oldURL;
    bool hashChange = equalIgnoringFragmentIdentifier(url, m_URL) && url.fragmentIdentifier() != m_URL.fragmentIdentifier();
    oldURL = m_URL;
    
    m_URL = url;
    history()->updateForSameDocumentNavigation();

    if (hashChange)
        m_frame->eventHandler()->stopAutoscrollTimer();
    
    started();

    if (FrameView* view = m_frame->view())
        view->scrollToFragment(m_URL);
    
    m_isComplete = false;
    checkCompleted();

    if (isNewNavigation) {
        checkLoadComplete();
    }

    m_client->dispatchDidNavigateWithinPage();

    if (stateObject) {
        m_frame->document()->statePopped(stateObject);
        m_client->dispatchDidPopStateWithinPage();
    }
    
    if (hashChange) {
        m_frame->document()->enqueueHashchangeEvent(oldURL, url);
        m_client->dispatchDidChangeLocationWithinPage();
    }
    
    m_client->didFinishLoad();
}
