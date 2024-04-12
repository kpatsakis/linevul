ReadUserLogFileState::getFileEventNum( int64_t &num ) const
{
	if ( NULL == m_ro_state ) {
		return false;
	}
	num = m_ro_state->internal.m_event_num.asint;
	return true;
}
