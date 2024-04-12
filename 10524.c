void XSSAuditor::initForFragment()
{
    ASSERT(isMainThread());
    ASSERT(m_state == Uninitialized);
    m_state = FilteringTokens;
    ASSERT(!m_isEnabled);
}
