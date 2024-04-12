void CL_Disconnect( qboolean showMainMenu ) {
	if ( !com_cl_running || !com_cl_running->integer ) {
		return;
	}

	Cvar_Set( "r_uiFullScreen", "1" );

	if ( clc.demorecording ) {
		CL_StopRecord_f();
	}

	if ( clc.download ) {
		FS_FCloseFile( clc.download );
		clc.download = 0;
	}
	*clc.downloadTempName = *clc.downloadName = 0;
	Cvar_Set( "cl_downloadName", "" );

#ifdef USE_MUMBLE
	if (cl_useMumble->integer && mumble_islinked()) {
		Com_Printf("Mumble: Unlinking from Mumble application\n");
		mumble_unlink();
	}
#endif

#ifdef USE_VOIP
	if (cl_voipSend->integer) {
		int tmp = cl_voipUseVAD->integer;
		cl_voipUseVAD->integer = 0;  // disable this for a moment.
		clc.voipOutgoingDataSize = 0;  // dump any pending VoIP transmission.
		Cvar_Set("cl_voipSend", "0");
		CL_CaptureVoip();  // clean up any state...
		cl_voipUseVAD->integer = tmp;
	}

	if (clc.voipCodecInitialized) {
		int i;
		opus_encoder_destroy(clc.opusEncoder);
		for (i = 0; i < MAX_CLIENTS; i++) {
			opus_decoder_destroy(clc.opusDecoder[i]);
		}
		clc.voipCodecInitialized = qfalse;
	}
	Cmd_RemoveCommand ("voip");
#endif

	if ( clc.demofile ) {
		FS_FCloseFile( clc.demofile );
		clc.demofile = 0;
	}

	if ( uivm && showMainMenu ) {
		VM_Call( uivm, UI_SET_ACTIVE_MENU, UIMENU_NONE );
	}

	SCR_StopCinematic();
	S_ClearSoundBuffer();

	if ( clc.state >= CA_CONNECTED ) {
		CL_AddReliableCommand("disconnect", qtrue);
		CL_WritePacket();
		CL_WritePacket();
		CL_WritePacket();
	}

	FS_PureServerSetLoadedPaks("", "");
	FS_PureServerSetReferencedPaks( "", "" );

	CL_ClearState();

	Com_Memset( &clc, 0, sizeof( clc ) );

	clc.state = CA_DISCONNECTED;

	Cvar_Set( "sv_cheats", "1" );

	cl_connectedToPureServer = qfalse;

#ifdef USE_VOIP
	clc.voipEnabled = qfalse;
#endif

	if( CL_VideoRecording( ) ) {
		SCR_UpdateScreen( );
		CL_CloseAVI( );
	}

	CL_UpdateGUID( NULL, 0 );

	if(!noGameRestart)
		CL_OldGame();
	else
		noGameRestart = qfalse;
}
