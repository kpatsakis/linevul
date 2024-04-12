int GahpClient::ec2_vm_start( const char * service_url,
							  const char * publickeyfile,
							  const char * privatekeyfile,
							  const char * ami_id, 
							  const char * keypair,
							  const char * user_data,
							  const char * user_data_file,
							  const char * instance_type,
							  const char * availability_zone,
							  const char * vpc_subnet,
							  const char * vpc_ip,
							  StringList & groupnames,
							  char * &instance_id,
							  char * &error_code)
{
	static const char* command = "EC2_VM_START";

	if  (server->m_commands_supported->contains_anycase(command)==FALSE) {
		return GAHPCLIENT_COMMAND_NOT_SUPPORTED;
	}

	if ( (service_url == NULL) || (publickeyfile == NULL) || (privatekeyfile == NULL) || (ami_id == NULL) ) {
		return GAHPCLIENT_COMMAND_NOT_SUPPORTED;
	}


	if ( !keypair ) keypair = NULLSTRING;
	if ( !user_data ) user_data = NULLSTRING;
	if ( !user_data_file ) user_data_file = NULLSTRING;
	if ( !instance_type ) instance_type = NULLSTRING;
	if ( !availability_zone || 0==strlen(availability_zone) ) availability_zone = NULLSTRING;
	if ( !vpc_subnet || 0==strlen(vpc_subnet) ) vpc_subnet = NULLSTRING;
	if ( !vpc_ip || 0==strlen(vpc_ip) ) vpc_ip = NULLSTRING;

						
	std::string reqline;

	char* esc1 = strdup( escapeGahpString(service_url) );
	char* esc2 = strdup( escapeGahpString(publickeyfile) );
	char* esc3 = strdup( escapeGahpString(privatekeyfile) );
	char* esc4 = strdup( escapeGahpString(ami_id) );
	char* esc5 = strdup( escapeGahpString(keypair) );
	char* esc6 = strdup( escapeGahpString(user_data) );
	char* esc7 = strdup( escapeGahpString(user_data_file) );

	char* esc8 = strdup( escapeGahpString(instance_type) );
	char* esc9 = strdup( escapeGahpString(availability_zone) );
	char* esc10 = strdup( escapeGahpString(vpc_subnet) );
	char* esc11 = strdup( escapeGahpString(vpc_ip) );

	int x = sprintf(reqline, "%s %s %s %s %s %s %s %s %s %s %s", esc1, esc2, esc3, esc4, esc5, esc6, esc7, esc8, esc9, esc10, esc11 );

	free( esc1 );
	free( esc2 );
	free( esc3 );
	free( esc4 );
	free( esc5 );
	free( esc6 );
	free( esc7 );
	free( esc8 );
	free( esc9 );
	free( esc10 );
	free( esc11 );
	ASSERT( x > 0 );

	const char * group_name;
	int cnt = 0;
	char * esc_groupname;

	groupnames.rewind();
	if ( groupnames.number() > 0 ) {
		while ( (group_name = groupnames.next()) ) {
			esc_groupname = strdup( escapeGahpString(group_name) );
			sprintf_cat(reqline, " %s", esc_groupname);
			cnt++;
			free( esc_groupname );
		}
	}
	ASSERT( cnt == groupnames.number() );
	const char *buf = reqline.c_str();
	if ( !is_pending(command,buf) ) {
		if ( m_mode == results_only ) {
			return GAHPCLIENT_COMMAND_NOT_SUBMITTED;
		}
		now_pending(command, buf, deleg_proxy);
	}


	Gahp_Args* result = get_pending_result(command, buf);

	
	if ( result ) {	
		int rc = 0;
		if ( result->argc == 2 ) {
			rc = atoi(result->argv[1]);
			if ( rc == 0 ) {
				EXCEPT( "Bad %s result", command );
				rc = 1;
			} else {
				error_string = "";
			}			
		} else if ( result->argc == 3 ) {
			rc = atoi(result->argv[1]);
			instance_id = strdup(result->argv[2]);
		} else if ( result->argc == 4 ) {
			rc = atoi( result->argv[1] );
 			error_code = strdup(result->argv[2]);	
 			error_string = result->argv[3];		
		} else {
			EXCEPT( "Bad %s result", command );
		}

		delete result;
		return rc;
	}

	if ( check_pending_timeout(command, buf) ) 
	{
		sprintf( error_string, "%s timed out", command );
		return GAHPCLIENT_COMMAND_TIMED_OUT;
	}

	return GAHPCLIENT_COMMAND_PENDING;	
}
