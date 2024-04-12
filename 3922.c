GahpClient::blah_job_cancel(const char *job_id)
{
	static const char* command = "BLAH_JOB_CANCEL";

	if  (server->m_commands_supported->contains_anycase(command)==FALSE) {
		return GAHPCLIENT_COMMAND_NOT_SUPPORTED;
	}

	if (!job_id) job_id=NULLSTRING;
	std::string reqline;
	int x = sprintf( reqline, "%s", escapeGahpString( job_id ) );
	ASSERT( x > 0 );
	const char *buf = reqline.c_str();

	if ( !is_pending(command,buf) ) {
		if ( m_mode == results_only ) {
			return GAHPCLIENT_COMMAND_NOT_SUBMITTED;
		}
		now_pending(command,buf,deleg_proxy);
	}

		
	Gahp_Args* result = get_pending_result(command,buf);
	if ( result ) {
		if (result->argc != 3) {
			EXCEPT("Bad %s Result",command);
		}
		int rc = atoi( result->argv[1] );
		if ( strcasecmp(result->argv[2], NULLSTRING) ) {
			error_string = result->argv[2];
		} else {
			error_string = "";
		}
		delete result;
		return rc;
	}

	if ( check_pending_timeout(command,buf) ) {
		sprintf( error_string, "%s timed out", command );
		return GAHPCLIENT_COMMAND_TIMED_OUT;
	}

	return GAHPCLIENT_COMMAND_PENDING;
}
