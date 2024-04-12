void CL_RequestAuthorization( void ) {
	char	nums[64];
	int		i, j, l;
	cvar_t	*fs;

	if ( !cls.authorizeServer.port ) {
		Com_Printf( "Resolving %s\n", AUTHORIZE_SERVER_NAME );
		if ( !NET_StringToAdr( AUTHORIZE_SERVER_NAME, &cls.authorizeServer, NA_IP ) ) {
			Com_Printf( "Couldn't resolve address\n" );
			return;
		}

		cls.authorizeServer.port = BigShort( PORT_AUTHORIZE );
		Com_Printf( "%s resolved to %i.%i.%i.%i:%i\n", AUTHORIZE_SERVER_NAME,
			cls.authorizeServer.ip[0], cls.authorizeServer.ip[1],
			cls.authorizeServer.ip[2], cls.authorizeServer.ip[3],
			BigShort( cls.authorizeServer.port ) );
	}
	if ( cls.authorizeServer.type == NA_BAD ) {
		return;
	}

	j = 0;
	l = strlen( cl_cdkey );
	if ( l > 32 ) {
		l = 32;
	}
	for ( i = 0 ; i < l ; i++ ) {
		if ( ( cl_cdkey[i] >= '0' && cl_cdkey[i] <= '9' )
				|| ( cl_cdkey[i] >= 'a' && cl_cdkey[i] <= 'z' )
				|| ( cl_cdkey[i] >= 'A' && cl_cdkey[i] <= 'Z' )
			 ) {
			nums[j] = cl_cdkey[i];
			j++;
		}
	}
	nums[j] = 0;

	fs = Cvar_Get ("cl_anonymous", "0", CVAR_INIT|CVAR_SYSTEMINFO );

	NET_OutOfBandPrint(NS_CLIENT, cls.authorizeServer, "getKeyAuthorize %i %s", fs->integer, nums );
}
