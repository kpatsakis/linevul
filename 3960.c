void StyleResolver::addTreeBoundaryCrossingRules(const Vector<MinimalRuleData>& rules, ContainerNode* scope)
{
    for (unsigned i = 0; i < rules.size(); ++i) {
        const MinimalRuleData& info = rules[i];
        m_treeBoundaryCrossingRules.addRule(info.m_rule, info.m_selectorIndex, scope, info.m_flags);
    }
}
