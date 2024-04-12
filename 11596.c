void Document::finishedParsing()
{
    DCHECK(!scriptableDocumentParser() || !m_parser->isParsing());
    DCHECK(!scriptableDocumentParser() || m_readyState != Loading);
    setParsingState(InDOMContentLoaded);
    DocumentParserTiming::from(*this).markParserStop();

    if (!m_documentTiming.domContentLoadedEventStart())
        m_documentTiming.markDomContentLoadedEventStart();
    dispatchEvent(Event::createBubble(EventTypeNames::DOMContentLoaded));
    if (!m_documentTiming.domContentLoadedEventEnd())
        m_documentTiming.markDomContentLoadedEventEnd();
    setParsingState(FinishedParsing);

    Microtask::performCheckpoint(V8PerIsolateData::mainThreadIsolate());

    if (LocalFrame* frame = this->frame()) {
        const bool mainResourceWasAlreadyRequested = frame->loader().stateMachine()->committedFirstRealDocumentLoad();

        if (mainResourceWasAlreadyRequested)
            updateStyleAndLayoutTree();

        beginLifecycleUpdatesIfRenderingReady();

        frame->loader().finishedParsing();

        TRACE_EVENT_INSTANT1("devtools.timeline", "MarkDOMContent", TRACE_EVENT_SCOPE_THREAD, "data", InspectorMarkLoadEvent::data(frame));
        InspectorInstrumentation::domContentLoadedEventFired(frame);
    }

    m_elementDataCacheClearTimer.startOneShot(10, BLINK_FROM_HERE);

    m_fetcher->clearPreloads(ResourceFetcher::ClearSpeculativeMarkupPreloads);
}
