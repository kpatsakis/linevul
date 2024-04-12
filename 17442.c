void Document::notifyLayoutTreeOfSubtreeChanges()
{
    if (!layoutView()->wasNotifiedOfSubtreeChange())
        return;

    m_lifecycle.advanceTo(DocumentLifecycle::InLayoutSubtreeChange);

    layoutView()->handleSubtreeModifications();
    DCHECK(!layoutView()->wasNotifiedOfSubtreeChange());

    m_lifecycle.advanceTo(DocumentLifecycle::LayoutSubtreeChangeClean);
}
