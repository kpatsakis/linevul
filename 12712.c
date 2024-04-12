void Document::dispatchUnloadEvents()
{
    RefPtrWillBeRawPtr<Document> protect(this);
    if (m_parser)
        m_parser->stopParsing();

    if (m_loadEventProgress == LoadEventNotRun)
        return;

    if (m_loadEventProgress <= UnloadEventInProgress) {
        Element* currentFocusedElement = focusedElement();
        if (isHTMLInputElement(currentFocusedElement))
            toHTMLInputElement(*currentFocusedElement).endEditing();
        if (m_loadEventProgress < PageHideInProgress) {
            m_loadEventProgress = PageHideInProgress;
            if (LocalDOMWindow* window = domWindow())
                window->dispatchEvent(PageTransitionEvent::create(EventTypeNames::pagehide, false), this);
            if (!m_frame)
                return;

            RefPtr<DocumentLoader> documentLoader =  m_frame->loader().provisionalDocumentLoader();
            m_loadEventProgress = UnloadEventInProgress;
            RefPtrWillBeRawPtr<Event> unloadEvent(Event::create(EventTypeNames::unload));
            if (documentLoader && !documentLoader->timing().unloadEventStart() && !documentLoader->timing().unloadEventEnd()) {
                DocumentLoadTiming& timing = documentLoader->timing();
                ASSERT(timing.navigationStart());
                timing.markUnloadEventStart();
                m_frame->localDOMWindow()->dispatchEvent(unloadEvent, this);
                timing.markUnloadEventEnd();
            } else {
                m_frame->localDOMWindow()->dispatchEvent(unloadEvent, m_frame->document());
            }
        }
        m_loadEventProgress = UnloadEventHandled;
    }

    if (!m_frame)
        return;

    bool keepEventListeners = m_frame->loader().stateMachine()->isDisplayingInitialEmptyDocument() && m_frame->loader().provisionalDocumentLoader()
        && isSecureTransitionTo(m_frame->loader().provisionalDocumentLoader()->url());
    if (!keepEventListeners)
        removeAllEventListenersRecursively();
}
