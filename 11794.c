GahpServer::command_use_cached_proxy( GahpProxyInfo *new_proxy )
{
	static const char *command = "USE_CACHED_PROXY";

	if  (m_commands_supported->contains_anycase(command)==FALSE) {
		return false;
	}

	if ( new_proxy == NULL ) {
		return false;
	}

	std::string buf;
	int x = sprintf(buf,"%s %d",command,new_proxy->proxy->id);
	ASSERT( x > 0 );
	write_line(buf.c_str());

	Gahp_Args result;
	read_argv(result);
	if ( result.argc == 0 || result.argv[0][0] != 'S' ) {
		char *reason;
		if ( result.argc > 1 ) {
			reason = result.argv[1];
		} else {
			reason = "Unspecified error";
		}
		dprintf(D_ALWAYS,"GAHP command '%s' failed: %s\n",command,reason);
		return false;
	}

	return true;
}
