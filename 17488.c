const char *FS_LoadedPakChecksums( void ) {
	static char info[BIG_INFO_STRING];
	searchpath_t    *search;

	info[0] = 0;

	for ( search = fs_searchpaths ; search ; search = search->next ) {
		if ( !search->pack ) {
			continue;
		}

		Q_strcat( info, sizeof( info ), va( "%i ", search->pack->checksum ) );
	}

	return info;
}
