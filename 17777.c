condor_auth_config(int is_daemon)
{
#if !defined(SKIP_AUTHENTICATION) && defined(HAVE_EXT_GLOBUS)

	if ( is_daemon ) {
		UnsetEnv( "X509_USER_PROXY" );
	}


	char *pbuf = 0;
	char *proxy_buf = 0;
	char *cert_buf = 0;
	char *key_buf = 0;
	char *trustedca_buf = 0;
	char *mapfile_buf = 0;

	MyString buffer;



	pbuf = param( STR_GSI_DAEMON_DIRECTORY );
	trustedca_buf = param( STR_GSI_DAEMON_TRUSTED_CA_DIR );
	mapfile_buf = param( STR_GSI_MAPFILE );
	if( is_daemon ) {
		proxy_buf = param( STR_GSI_DAEMON_PROXY );
		cert_buf = param( STR_GSI_DAEMON_CERT );
		key_buf = param( STR_GSI_DAEMON_KEY );
	}

	if (pbuf) {

		if( !trustedca_buf) {
			buffer.sprintf( "%s%ccertificates", pbuf, DIR_DELIM_CHAR);
			SetEnv( STR_GSI_CERT_DIR, buffer.Value() );
		}

		if (!mapfile_buf ) {
			buffer.sprintf( "%s%cgrid-mapfile", pbuf, DIR_DELIM_CHAR);
			SetEnv( STR_GSI_MAPFILE, buffer.Value() );
		}

		if( is_daemon ) {
			if( !cert_buf ) {
				buffer.sprintf( "%s%chostcert.pem", pbuf, DIR_DELIM_CHAR);
				SetEnv( STR_GSI_USER_CERT, buffer.Value() );
			}
	
			if (!key_buf ) {
				buffer.sprintf( "%s%chostkey.pem", pbuf, DIR_DELIM_CHAR);
				SetEnv( STR_GSI_USER_KEY, buffer.Value() );
			}
		}

		free( pbuf );
	}

	if(trustedca_buf) {
		SetEnv( STR_GSI_CERT_DIR, trustedca_buf );
		free(trustedca_buf);
	}

	if (mapfile_buf) {
		SetEnv( STR_GSI_MAPFILE, mapfile_buf );
		free(mapfile_buf);
	}

	if( is_daemon ) {
		if(proxy_buf) {
			SetEnv( STR_GSI_USER_PROXY, proxy_buf );
			free(proxy_buf);
		}

		if(cert_buf) {
			SetEnv( STR_GSI_USER_CERT, cert_buf );
			free(cert_buf);
		}

		if(key_buf) {
			SetEnv( STR_GSI_USER_KEY, key_buf );
			free(key_buf);
		}
	}

#else
	(void) is_daemon;	// Quiet 'unused parameter' warnings
#endif
}
