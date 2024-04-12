LayoutBlockFlow::LayoutBlockFlowRareData& LayoutBlockFlow::ensureRareData()
{
    if (m_rareData)
        return *m_rareData;

    m_rareData = adoptPtr(new LayoutBlockFlowRareData(this));
    return *m_rareData;
}
