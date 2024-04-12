void CL_ForwardCommandToServer( const char *string ) {
	char	*cmd;

	cmd = Cmd_Argv(0);

	if ( cmd[0] == '-' ) {
		return;
	}

	if ( clc.demoplaying || clc.state < CA_CONNECTED || cmd[0] == '+' ) {
		Com_Printf ("Unknown command \"%s" S_COLOR_WHITE "\"\n", cmd);
		return;
	}

	if ( Cmd_Argc() > 1 ) {
		CL_AddReliableCommand(string, qfalse);
	} else {
		CL_AddReliableCommand(cmd, qfalse);
	}
}
