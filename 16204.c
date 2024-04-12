bool LayoutBlockFlow::mustDiscardMarginBefore() const
{
    return style()->marginBeforeCollapse() == MDISCARD || (m_rareData && m_rareData->m_discardMarginBefore);
}
