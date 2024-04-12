InvalidationData& RuleFeatureSet::ensureAttributeInvalidationData(const AtomicString& attributeName)
{
    return ensureInvalidationData(m_attributeInvalidationSets, attributeName);
}
