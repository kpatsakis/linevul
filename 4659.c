int	FS_GetModList( char *listbuf, int bufsize ) {
	int		nMods, i, j, nTotal, nLen, nPaks, nPotential, nDescLen;
	char **pFiles = NULL;
	char **pPaks = NULL;
	char *name, *path;
	char description[MAX_OSPATH];

	int dummy;
	char **pFiles0 = NULL;
	char **pFiles1 = NULL;
#ifndef STANDALONE
	char **pFiles2 = NULL;
	char **pFiles3 = NULL;
#endif

	qboolean bDrop = qfalse;

	*listbuf = 0;
	nMods = nTotal = 0;

	pFiles0 = Sys_ListFiles( fs_homepath->string, NULL, NULL, &dummy, qtrue );
	pFiles1 = Sys_ListFiles( fs_basepath->string, NULL, NULL, &dummy, qtrue );
#ifndef STANDALONE
	pFiles2 = Sys_ListFiles( fs_steampath->string, NULL, NULL, &dummy, qtrue );
#endif
#ifndef STANDALONE
	pFiles3 = Sys_ConcatenateFileLists( pFiles0, pFiles1 );
	pFiles = Sys_ConcatenateFileLists( pFiles2, pFiles3 );
#else
	pFiles = Sys_ConcatenateFileLists( pFiles0, pFiles1 );
#endif

	nPotential = Sys_CountFileList(pFiles);

	for ( i = 0 ; i < nPotential ; i++ ) {
		name = pFiles[i];
		if (i!=0) {
			bDrop = qfalse;
			for(j=0; j<i; j++)
			{
				if (Q_stricmp(pFiles[j],name)==0) {
					bDrop = qtrue;
					break;
				}
			}
		}
		if (bDrop) {
			continue;
		}
		if (Q_stricmp(name, com_basegame->string) && Q_stricmpn(name, ".", 1)) {
			path = FS_BuildOSPath( fs_basepath->string, name, "" );
			nPaks = 0;
			pPaks = Sys_ListFiles(path, ".pk3", NULL, &nPaks, qfalse); 
			Sys_FreeFileList( pPaks ); // we only use Sys_ListFiles to check wether .pk3 files are present

			/* try on home path */
			if ( nPaks <= 0 )
			{
				path = FS_BuildOSPath( fs_homepath->string, name, "" );
				nPaks = 0;
				pPaks = Sys_ListFiles( path, ".pk3", NULL, &nPaks, qfalse );
				Sys_FreeFileList( pPaks );
			}

#ifndef STANDALONE
			/* try on steam path */
			if ( nPaks <= 0 )
			{
				path = FS_BuildOSPath( fs_steampath->string, name, "" );
				nPaks = 0;
				pPaks = Sys_ListFiles( path, ".pk3", NULL, &nPaks, qfalse );
				Sys_FreeFileList( pPaks );
			}
#endif

			if (nPaks > 0) {
				nLen = strlen(name) + 1;
				FS_GetModDescription( name, description, sizeof( description ) );
				nDescLen = strlen(description) + 1;

				if (nTotal + nLen + 1 + nDescLen + 1 < bufsize) {
					strcpy(listbuf, name);
					listbuf += nLen;
					strcpy(listbuf, description);
					listbuf += nDescLen;
					nTotal += nLen + nDescLen;
					nMods++;
				}
				else {
					break;
				}
			}
		}
	}
	Sys_FreeFileList( pFiles );

	return nMods;
}
