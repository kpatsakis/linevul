ShadowRoot::~ShadowRoot()
{
    ASSERT(!m_prev);
    ASSERT(!m_next);

    if (hasRareData())
        clearRareData();
}
