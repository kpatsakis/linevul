void CL_ServerInfoPacket( netadr_t from, msg_t *msg ) {
	int	i, type;
	char	info[MAX_INFO_STRING];
	char	*infoString;
	int	prot;
	char	*gamename;
	qboolean gameMismatch;

	infoString = MSG_ReadString( msg );

	gamename = Info_ValueForKey( infoString, "gamename" );

#ifdef LEGACY_PROTOCOL
	if (com_legacyprotocol->integer && !*gamename)
		gameMismatch = qfalse;
	else
#endif
		gameMismatch = !*gamename || strcmp(gamename, com_gamename->string) != 0;

	if (gameMismatch)
	{
		Com_DPrintf( "Game mismatch in info packet: %s\n", infoString );
		return;
	}

	prot = atoi( Info_ValueForKey( infoString, "protocol" ) );

	if(prot != com_protocol->integer
#ifdef LEGACY_PROTOCOL
	   && prot != com_legacyprotocol->integer
#endif
	  )
	{
		Com_DPrintf( "Different protocol info packet: %s\n", infoString );
	}

	for ( i = 0; i < MAX_PINGREQUESTS; i++ )
	{
		if ( cl_pinglist[i].adr.port && !cl_pinglist[i].time && NET_CompareAdr( from, cl_pinglist[i].adr ) ) {
			cl_pinglist[i].time = Sys_Milliseconds() - cl_pinglist[i].start;
			Com_DPrintf( "ping time %dms from %s\n", cl_pinglist[i].time, NET_AdrToString( from ) );

			Q_strncpyz( cl_pinglist[i].info, infoString, sizeof( cl_pinglist[i].info ) );

			switch ( from.type )
			{
			case NA_BROADCAST:
			case NA_IP:
				type = 1;
				break;
			case NA_IP6:
				type = 2;
				break;
			default:
				type = 0;
				break;
			}
			Info_SetValueForKey( cl_pinglist[i].info, "nettype", va( "%d", type ) );
			CL_SetServerInfoByAddress( from, infoString, cl_pinglist[i].time );

			return;
		}
	}

	if ( cls.pingUpdateSource != AS_LOCAL ) {
		return;
	}

	for ( i = 0 ; i < MAX_OTHER_SERVERS ; i++ ) {
		if ( cls.localServers[i].adr.port == 0 ) {
			break;
		}

		if ( NET_CompareAdr( from, cls.localServers[i].adr ) ) {
			return;
		}
	}

	if ( i == MAX_OTHER_SERVERS ) {
		Com_DPrintf( "MAX_OTHER_SERVERS hit, dropping infoResponse\n" );
		return;
	}

	cls.numlocalservers = i + 1;
	CL_InitServerInfo( &cls.localServers[i], &from );

	Q_strncpyz( info, MSG_ReadString( msg ), MAX_INFO_STRING );
	if ( strlen( info ) ) {
		if ( info[strlen( info ) - 1] != '\n' ) {
			Q_strcat( info, sizeof(info), "\n" );
		}
		Com_Printf( "%s: %s", NET_AdrToStringwPort( from ), info );
	}
}
