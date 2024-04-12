void ContainerNode::checkForChildrenAdjacentRuleChanges()
{
    bool hasDirectAdjacentRules = childrenAffectedByDirectAdjacentRules();
    bool hasIndirectAdjacentRules = childrenAffectedByIndirectAdjacentRules();

    if (!hasDirectAdjacentRules && !hasIndirectAdjacentRules)
        return;

    unsigned forceCheckOfNextElementCount = 0;
    bool forceCheckOfAnyElementSibling = false;
    Document& document = this->document();

    for (Element* child = ElementTraversal::firstChild(*this); child; child = ElementTraversal::nextSibling(*child)) {
        bool childRulesChanged = child->needsStyleRecalc() && child->styleChangeType() >= SubtreeStyleChange;

        if (forceCheckOfNextElementCount || forceCheckOfAnyElementSibling)
            child->setNeedsStyleRecalc(SubtreeStyleChange, StyleChangeReasonForTracing::create(StyleChangeReason::SiblingSelector));

        if (childRulesChanged && hasDirectAdjacentRules)
            forceCheckOfNextElementCount = document.styleEngine().maxDirectAdjacentSelectors();
        else if (forceCheckOfNextElementCount)
            --forceCheckOfNextElementCount;

        forceCheckOfAnyElementSibling = forceCheckOfAnyElementSibling || (childRulesChanged && hasIndirectAdjacentRules);
    }
}
