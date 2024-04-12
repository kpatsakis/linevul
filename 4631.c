GahpClient::gt4_set_termination_time(const char *resource_uri,
									 time_t &new_termination_time)
{
	static const char* command = "GT4_SET_TERMINATION_TIME";

	if  (server->m_commands_supported->contains_anycase(command)==FALSE) {
		return GAHPCLIENT_COMMAND_NOT_SUPPORTED;
	}

	if (!resource_uri) resource_uri=NULLSTRING;
	std::string reqline;
	int x = sprintf(reqline,"%s %ld",escapeGahpString(resource_uri),
							 new_termination_time);
	ASSERT( x > 0 );
	const char *buf = reqline.c_str();

	if ( !is_pending(command,buf) ) {
		if ( m_mode == results_only ) {
			return GAHPCLIENT_COMMAND_NOT_SUBMITTED;
		}
		now_pending(command,buf,normal_proxy);
	}

		
	Gahp_Args* result = get_pending_result(command,buf);
	if ( result ) {
		if (result->argc != 4) {
			EXCEPT("Bad %s Result",command);
		}
		int rc = atoi(result->argv[1]);
		if ( strcasecmp(result->argv[3], NULLSTRING) ) {
			error_string = result->argv[3];
		} else {
			error_string = "";
		}
		new_termination_time = atoi(result->argv[2]);
		delete result;
		return rc;
	}

	if ( check_pending_timeout(command,buf) ) {
		sprintf( error_string, "%s timed out", command );
		return GAHPCLIENT_COMMAND_TIMED_OUT;
	}

	return GAHPCLIENT_COMMAND_PENDING;
}
