void QDECL Com_Error( int code, const char *fmt, ... ) {
	va_list argptr;
	static int lastErrorTime;
	static int errorCount;
	int currentTime;
	qboolean restartClient;

	if(com_errorEntered)
		Sys_Error("recursive error after: %s", com_errorMessage);

	com_errorEntered = qtrue;

	Cvar_Set("com_errorCode", va("%i", code));

	if ( com_buildScript && com_buildScript->integer ) {
		code = ERR_FATAL;
	}

	currentTime = Sys_Milliseconds();
	if ( currentTime - lastErrorTime < 100 ) {
		if ( ++errorCount > 3 ) {
			code = ERR_FATAL;
		}
	} else {
		errorCount = 0;
	}
	lastErrorTime = currentTime;

	va_start( argptr,fmt );
	Q_vsnprintf (com_errorMessage, sizeof(com_errorMessage),fmt,argptr);
	va_end( argptr );

	if (code != ERR_DISCONNECT && code != ERR_NEED_CD)
		Cvar_Set( "com_errorMessage", com_errorMessage );

	restartClient = com_gameClientRestarting && !( com_cl_running && com_cl_running->integer );

	com_gameRestarting = qfalse;
	com_gameClientRestarting = qfalse;

	if (code == ERR_DISCONNECT || code == ERR_SERVERDISCONNECT) {
		VM_Forced_Unload_Start();
		SV_Shutdown( "Server disconnected" );
		if ( restartClient ) {
			CL_Init();
		}
		CL_Disconnect( qtrue );
		CL_FlushMemory();
		VM_Forced_Unload_Done();
		FS_PureServerSetLoadedPaks("", "");
		com_errorEntered = qfalse;
		longjmp( abortframe, -1 );
	} else if (code == ERR_DROP) {
		Com_Printf( "********************\nERROR: %s\n********************\n", com_errorMessage );
		VM_Forced_Unload_Start();
		SV_Shutdown (va("Server crashed: %s",  com_errorMessage));
		if ( restartClient ) {
			CL_Init();
		}
		CL_Disconnect( qtrue );
		CL_FlushMemory();
		VM_Forced_Unload_Done();
		FS_PureServerSetLoadedPaks("", "");
		com_errorEntered = qfalse;
		longjmp( abortframe, -1 );
	} else if ( code == ERR_NEED_CD ) {
		VM_Forced_Unload_Start();
		SV_Shutdown( "Server didn't have CD" );
		if ( restartClient ) {
			CL_Init();
		}
		if ( com_cl_running && com_cl_running->integer ) {
			CL_Disconnect( qtrue );
			CL_FlushMemory();
			VM_Forced_Unload_Done();
			CL_CDDialog();
		} else {
			Com_Printf( "Server didn't have CD\n" );
			VM_Forced_Unload_Done();
		}

		FS_PureServerSetLoadedPaks("", "");

		com_errorEntered = qfalse;
		longjmp( abortframe, -1 );
	} else {
		VM_Forced_Unload_Start();
		CL_Shutdown(va("Client fatal crashed: %s", com_errorMessage), qtrue, qtrue);
		SV_Shutdown(va("Server fatal crashed: %s", com_errorMessage));
		VM_Forced_Unload_Done();
	}

	Com_Shutdown();

	Sys_Error( "%s", com_errorMessage );
}
