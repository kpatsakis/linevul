void Document::dispose()
{
    ASSERT_WITH_SECURITY_IMPLICATION(!m_deletionHasBegun);

    m_docType = nullptr;
    m_focusedElement = nullptr;
    m_hoverNode = nullptr;
    m_activeHoverElement = nullptr;
    m_titleElement = nullptr;
    m_documentElement = nullptr;
    m_contextFeatures = ContextFeatures::defaultSwitch();
    m_userActionElements.documentDidRemoveLastRef();
    m_associatedFormControls.clear();

    m_scriptRunner->dispose();
    detachParser();

    m_registrationContext.clear();

    destroyTreeScopeData();

    removeDetachedChildren();

    m_formController.clear();

    m_markers->clear();

    if (m_scriptedAnimationController)
        m_scriptedAnimationController->clearDocumentPointer();
    m_scriptedAnimationController.clear();

    m_scriptedIdleTaskController.clear();

    if (svgExtensions())
        accessSVGExtensions().pauseAnimations();

    if (m_intersectionObserverData)
        m_intersectionObserverData->dispose();

    m_lifecycle.advanceTo(DocumentLifecycle::Disposed);
    DocumentLifecycleNotifier::notifyDocumentWasDisposed();

    m_canvasFontCache.clear();
}
