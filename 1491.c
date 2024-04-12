GahpClient::gt4_gram_client_job_status(const char * job_contact,
	char ** job_status, char ** job_fault, int * exit_code)
{
	static const char* command = "GT4_GRAM_JOB_STATUS";

	if  (server->m_commands_supported->contains_anycase(command)==FALSE) {
		return GAHPCLIENT_COMMAND_NOT_SUPPORTED;
	}

	if (!job_contact) job_contact=NULLSTRING;
	std::string reqline;
	int x = sprintf(reqline,"%s",escapeGahpString(job_contact));
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
		if (result->argc != 6) {
			EXCEPT("Bad %s Result",command);
		}
		int rc = atoi(result->argv[1]);
		if ( strcasecmp( result->argv[2], NULLSTRING ) ) {
			*job_status = strdup( result->argv[2] );
		} else {
			*job_status = NULL;
		}
		if ( strcasecmp( result->argv[3], NULLSTRING ) ) {
			*job_fault = strdup( result->argv[3] );
		} else {
			*job_fault = NULL;
		}
		if ( strcasecmp(result->argv[4], NULLSTRING) ) {
			*exit_code = atoi( result->argv[4] );
		} else {
			*exit_code = GT4_NO_EXIT_CODE;
		}
		if ( strcasecmp(result->argv[5], NULLSTRING) ) {
			error_string = result->argv[5];
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
