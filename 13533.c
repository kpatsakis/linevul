static void CL_Cache_EndGather_f( void ) {
	int i, j, handle, cachePass;
	char filename[MAX_QPATH];

	cachePass = (int)floor( (float)cacheIndex * CACHE_HIT_RATIO );

	for ( i = 0; i < CACHE_NUMGROUPS; i++ ) {
		Q_strncpyz( filename, cacheGroups[i].name, MAX_QPATH );
		Q_strcat( filename, MAX_QPATH, ".cache" );

		handle = FS_FOpenFileWrite( filename );

		for ( j = 0; j < MAX_CACHE_ITEMS; j++ ) {
			if ( cacheItems[i][j].hits >= cachePass && strstr( cacheItems[i][j].name, "/" ) ) {
				FS_Write( cacheItems[i][j].name, strlen( cacheItems[i][j].name ), handle );
				FS_Write( "\n", 1, handle );
			}
		}

		FS_FCloseFile( handle );
	}

	Cvar_Set( "cl_cacheGathering", "0" );
}
