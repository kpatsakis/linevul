CStarter::WriteRecoveryFile( ClassAd *recovery_ad )
{
	MyString tmp_file;
	FILE *tmp_fp;

	if ( recovery_ad == NULL ) {
		return;
	}

	if ( m_recoveryFile.Length() == 0 ) {
		m_recoveryFile.sprintf( "%s%cdir_%ld.recover", Execute,
								DIR_DELIM_CHAR, (long)daemonCore->getpid() );
	}

	tmp_file.sprintf( "%s.tmp", m_recoveryFile.Value() );

	tmp_fp = safe_fcreate_replace_if_exists( tmp_file.Value(), "w" );
	if ( tmp_fp == NULL ) {
		dprintf( D_ALWAYS, "Failed to open recovery file %s\n", tmp_file.Value() );
		return;
	}

	if ( recovery_ad->fPrint( tmp_fp ) == FALSE ) {
		dprintf( D_ALWAYS, "Failed to write recovery file\n" );
		fclose( tmp_fp );
		return;
	}

	if ( fclose( tmp_fp ) != 0 ) {
		dprintf( D_ALWAYS, "Failed close recovery file\n" );
		unlink( tmp_file.Value() );
		return;
	}

	if ( rotate_file( tmp_file.Value(), m_recoveryFile.Value() ) != 0 ) {
		dprintf( D_ALWAYS, "Failed to rename recovery file\n" );
		unlink( tmp_file.Value() );
	}
}
