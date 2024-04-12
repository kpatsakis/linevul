void Document::notifyLayoutTreeOfSubtreeChanges()
{
    if (!layoutView()->wasNotifiedOfSubtreeChange())
        return;

    m_lifecycle.advanceTo(DocumentLifecycle::InLayoutSubtreeChange);

    layoutView()->handleSubtreeModifications();
    ASSERT(!layoutView()->wasNotifiedOfSubtreeChange());

    m_lifecycle.advanceTo(DocumentLifecycle::LayoutSubtreeChangeClean);
}
