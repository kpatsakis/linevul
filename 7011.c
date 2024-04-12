PassRefPtr<Range> Range::cloneRange(ExceptionCode& ec) const
{
    if (!m_start.container()) {
        ec = INVALID_STATE_ERR;
        return 0;
    }

    return Range::create(m_ownerDocument, m_start.container(), m_start.offset(), m_end.container(), m_end.offset());
}
