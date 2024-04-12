void CL_InitDownloads(void) {
  char missingfiles[1024];

  if ( !(cl_allowDownload->integer & DLF_ENABLE) )
  {
    if (FS_ComparePaks( missingfiles, sizeof( missingfiles ), qfalse ) )
    {      
      Com_Printf( "\nWARNING: You are missing some files referenced by the server:\n%s"
                  "You might not be able to join the game\n"
                  "Go to the setting menu to turn on autodownload, or get the file elsewhere\n\n", missingfiles );
    }
  }
  else if ( FS_ComparePaks( clc.downloadList, sizeof( clc.downloadList ) , qtrue ) ) {

    Com_Printf("Need paks: %s\n", clc.downloadList );

		if ( *clc.downloadList ) {
			clc.state = CA_CONNECTED;

			*clc.downloadTempName = *clc.downloadName = 0;
			Cvar_Set( "cl_downloadName", "" );

			CL_NextDownload();
			return;
		}

	}
		
	CL_DownloadsComplete();
}
