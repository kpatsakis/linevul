void ContainerNode::setHovered(bool over)
{
    if (over == hovered())
        return;

    Node::setHovered(over);

    if (!layoutObject()) {
        if (over)
            return;
        if (isElementNode() && toElement(this)->childrenOrSiblingsAffectedByHover() && styleChangeType() < SubtreeStyleChange)
            document().styleEngine().pseudoStateChangedForElement(CSSSelector::PseudoHover, *toElement(this));
        else
            setNeedsStyleRecalc(LocalStyleChange, StyleChangeReasonForTracing::createWithExtraData(StyleChangeReason::PseudoClass, StyleChangeExtraData::Hover));
        return;
    }

    if (styleChangeType() < SubtreeStyleChange) {
        if (computedStyle()->affectedByHover() && computedStyle()->hasPseudoStyle(FIRST_LETTER))
            setNeedsStyleRecalc(SubtreeStyleChange, StyleChangeReasonForTracing::createWithExtraData(StyleChangeReason::PseudoClass, StyleChangeExtraData::Hover));
        else if (isElementNode() && toElement(this)->childrenOrSiblingsAffectedByHover())
            document().styleEngine().pseudoStateChangedForElement(CSSSelector::PseudoHover, *toElement(this));
        else if (computedStyle()->affectedByHover())
            setNeedsStyleRecalc(LocalStyleChange, StyleChangeReasonForTracing::createWithExtraData(StyleChangeReason::PseudoClass, StyleChangeExtraData::Hover));
    }

    LayoutTheme::theme().controlStateChanged(*layoutObject(), HoverControlState);
}
