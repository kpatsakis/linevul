void Document::updateStyleAndLayout()
{
    DCHECK(isMainThread());

    ScriptForbiddenScope forbidScript;

    FrameView* frameView = view();
    if (frameView && frameView->isInPerformLayout()) {
        ASSERT_NOT_REACHED();
        return;
    }

    if (HTMLFrameOwnerElement* owner = localOwner())
        owner->document().updateStyleAndLayout();

    updateStyleAndLayoutTree();

    if (!isActive())
        return;

    if (frameView->needsLayout())
        frameView->layout();

    if (lifecycle().state() < DocumentLifecycle::LayoutClean)
        lifecycle().advanceTo(DocumentLifecycle::LayoutClean);
}
