void ContainerNode::setFocus(bool received)
{
    if (ShadowRoot* root = containingShadowRoot()) {
        if (root->type() != ShadowRootType::UserAgent)
            shadowHost()->setFocus(received);
    }

    if (isElementNode() && document().focusedElement() && document().focusedElement() != this) {
        if (toElement(this)->authorShadowRoot())
            received = received && toElement(this)->authorShadowRoot()->delegatesFocus();
    }

    if (focused() == received)
        return;

    Node::setFocus(received);

    focusStateChanged();

    if (layoutObject() || received)
        return;

    if (isElementNode() && toElement(this)->childrenOrSiblingsAffectedByFocus() && styleChangeType() < SubtreeStyleChange)
        document().styleEngine().pseudoStateChangedForElement(CSSSelector::PseudoFocus, *toElement(this));
    else
        setNeedsStyleRecalc(LocalStyleChange, StyleChangeReasonForTracing::createWithExtraData(StyleChangeReason::PseudoClass, StyleChangeExtraData::Focus));
}
