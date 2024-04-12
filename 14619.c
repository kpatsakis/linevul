Document::Document(const DocumentInit& initializer, DocumentClassFlags documentClasses)
    : ContainerNode(0, CreateDocument)
    , TreeScope(*this)
    , m_hasNodesWithPlaceholderStyle(false)
    , m_evaluateMediaQueriesOnStyleRecalc(false)
    , m_pendingSheetLayout(NoLayoutWithPendingSheets)
    , m_frame(initializer.frame())
    , m_domWindow(m_frame ? m_frame->localDOMWindow() : 0)
    , m_importsController(initializer.importsController())
    , m_activeParserCount(0)
    , m_contextFeatures(ContextFeatures::defaultSwitch())
    , m_wellFormed(false)
    , m_printing(false)
    , m_paginatedForScreen(false)
    , m_compatibilityMode(NoQuirksMode)
    , m_compatibilityModeLocked(false)
    , m_executeScriptsWaitingForResourcesTimer(this, &Document::executeScriptsWaitingForResourcesTimerFired)
    , m_hasAutofocused(false)
    , m_clearFocusedElementTimer(this, &Document::clearFocusedElementTimerFired)
    , m_domTreeVersion(++s_globalTreeVersion)
    , m_styleVersion(0)
    , m_listenerTypes(0)
    , m_mutationObserverTypes(0)
    , m_visitedLinkState(VisitedLinkState::create(*this))
    , m_visuallyOrdered(false)
    , m_readyState(Complete)
    , m_parsingState(FinishedParsing)
    , m_gotoAnchorNeededAfterStylesheetsLoad(false)
    , m_containsValidityStyleRules(false)
    , m_updateFocusAppearanceRestoresSelection(false)
    , m_containsPlugins(false)
    , m_ignoreDestructiveWriteCount(0)
    , m_markers(adoptPtrWillBeNoop(new DocumentMarkerController))
    , m_updateFocusAppearanceTimer(this, &Document::updateFocusAppearanceTimerFired)
    , m_cssTarget(nullptr)
    , m_loadEventProgress(LoadEventNotRun)
    , m_startTime(currentTime())
    , m_scriptRunner(ScriptRunner::create(this))
    , m_xmlVersion("1.0")
    , m_xmlStandalone(StandaloneUnspecified)
    , m_hasXMLDeclaration(0)
    , m_designMode(false)
    , m_hasAnnotatedRegions(false)
    , m_annotatedRegionsDirty(false)
    , m_useSecureKeyboardEntryWhenActive(false)
    , m_documentClasses(documentClasses)
    , m_isViewSource(false)
    , m_sawElementsInKnownNamespaces(false)
    , m_isSrcdocDocument(false)
    , m_isMobileDocument(false)
    , m_layoutView(0)
#if !ENABLE(OILPAN)
    , m_weakFactory(this)
#endif
    , m_contextDocument(initializer.contextDocument())
    , m_hasFullscreenSupplement(false)
    , m_loadEventDelayCount(0)
    , m_loadEventDelayTimer(this, &Document::loadEventDelayTimerFired)
    , m_pluginLoadingTimer(this, &Document::pluginLoadingTimerFired)
    , m_writeRecursionIsTooDeep(false)
    , m_writeRecursionDepth(0)
    , m_taskRunner(MainThreadTaskRunner::create(this))
    , m_registrationContext(initializer.registrationContext(this))
    , m_elementDataCacheClearTimer(this, &Document::elementDataCacheClearTimerFired)
    , m_timeline(AnimationTimeline::create(this))
    , m_templateDocumentHost(nullptr)
    , m_didAssociateFormControlsTimer(this, &Document::didAssociateFormControlsTimerFired)
    , m_hasViewportUnits(false)
    , m_styleRecalcElementCounter(0)
    , m_parserSyncPolicy(AllowAsynchronousParsing)
{
    if (m_frame) {
        ASSERT(m_frame->page());
        provideContextFeaturesToDocumentFrom(*this, *m_frame->page());

        m_fetcher = m_frame->loader().documentLoader()->fetcher();
        FrameFetchContext::provideDocumentToContext(m_fetcher->context(), this);
    } else if (m_importsController) {
        m_fetcher = FrameFetchContext::createContextAndFetcher(nullptr);
        FrameFetchContext::provideDocumentToContext(m_fetcher->context(), this);
    } else {
        m_fetcher = ResourceFetcher::create(nullptr);
    }

    if (initializer.shouldSetURL())
        setURL(initializer.url());

    initSecurityContext(initializer);
    initDNSPrefetch();

#if !ENABLE(OILPAN)
    for (unsigned i = 0; i < WTF_ARRAY_LENGTH(m_nodeListCounts); ++i)
        m_nodeListCounts[i] = 0;
#endif

    InspectorCounters::incrementCounter(InspectorCounters::DocumentCounter);

    m_lifecycle.advanceTo(DocumentLifecycle::Inactive);

    m_styleEngine = StyleEngine::create(*this);

    ASSERT(!parentDocument() || !parentDocument()->activeDOMObjectsAreSuspended());

#ifndef NDEBUG
    liveDocumentSet().add(this);
#endif
}
