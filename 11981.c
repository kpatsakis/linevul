void Document::setCompatibilityMode(CompatibilityMode mode)
{
    if (m_compatibilityModeLocked || mode == m_compatibilityMode)
        return;
    bool wasInQuirksMode = inQuirksMode();
    m_compatibilityMode = mode;
    selectorQueryCache()->invalidate();
    if (inQuirksMode() != wasInQuirksMode) {
        m_styleSheetCollection->clearPageUserSheet();
        m_styleSheetCollection->invalidateInjectedStyleSheetCache();
    }
}
