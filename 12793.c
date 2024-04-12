ReadUserLogState::CheckFileStatus( int fd, bool &is_empty )
{
	StatWrapper	sb;

	if ( fd >= 0 ) {
		(void) sb.Stat( fd );
	}

	if ( m_cur_path.Length() && !sb.IsBufValid() ) {
		(void) sb.Stat( m_cur_path.Value() );
	}

	if ( sb.GetRc() ) {
		dprintf( D_FULLDEBUG, "StatFile: errno = %d\n", sb.GetErrno() );
		return ReadUserLog::LOG_STATUS_ERROR;
	}

	filesize_t				size = sb.GetBuf()->st_size;
	ReadUserLog::FileStatus status;

	if ( 0 == size ) {
		is_empty = true;
		if ( m_status_size < 0 ) {
			m_status_size = 0;
		}
	}
	else {
		is_empty = false;
	}
	if ( (m_status_size < 0) || (size > m_status_size) ) {
		status = ReadUserLog::LOG_STATUS_GROWN;
	}
	else if ( size == m_status_size ) {
		status = ReadUserLog::LOG_STATUS_NOCHANGE;
	}
	else {
		status = ReadUserLog::LOG_STATUS_SHRUNK;
	}
	m_status_size = size;
	Update();
	return status;
}
