static inline void notifyTargetAboutAnimValChange(SVGElement* targetElement, const QualifiedName& attributeName)
{
    ASSERT_WITH_SECURITY_IMPLICATION(!targetElement->m_deletionHasBegun);
    targetElement->svgAttributeChanged(attributeName);
}
