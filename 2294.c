GahpServer::RemoveGahpClient()
{
	m_reference_count--;

	if ( m_reference_count <= 0 ) {
		m_deleteMeTid = daemonCore->Register_Timer( 30,
								(TimerHandlercpp)&GahpServer::DeleteMe,
								"GahpServer::DeleteMe", (Service*)this );
	}
}
