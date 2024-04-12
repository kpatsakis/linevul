GahpServer::command_async_mode_on()
{
	static const char* command = "ASYNC_MODE_ON";

	if  (m_commands_supported->contains_anycase(command)==FALSE) {
		return false;
	}

	write_line(command);
	Gahp_Args result;
	read_argv(result);
	if ( result.argc == 0 || result.argv[0][0] != 'S' ) {
		dprintf(D_ALWAYS,"GAHP command '%s' failed\n",command);
		return false;
	}

	return true;
}
