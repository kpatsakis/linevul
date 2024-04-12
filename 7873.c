EventHandler::install()
{
	NameTableIterator next_sig( SigNames );
	struct sigaction action;
	int		i;
	int		signo;

	dprintf( D_FULLDEBUG, "EventHandler::install() {\n" );

	if( is_installed ) {
		EXCEPT( "ERROR EventHandler::install(), already installed" );
	}


	for( i=0; i<N_POSIX_SIGS; i++ ) {
		signo = next_sig();
		if( sigismember(&mask,signo) ) {
#if (defined(LINUX) && !defined(GLIBC20) && !defined(GLIBC21)) || defined(AIX) || defined(HPUX11) || defined(CONDOR_FREEBSD) || defined(Darwin) || defined(Solaris)
			action.sa_handler = func;
#else
			action.sa_handler = (void (*)(...)) func;
#endif

			action.sa_mask = mask;
			action.sa_flags = SA_NOCLDSTOP;
			if( sigaction(signo,&action,&o_action[i]) < 0 ) {
				perror( "sigaction" );
				exit( 1 );
			}
			dprintf( D_FULLDEBUG,
				"\t*FSM* Installed handler %p for signal %s, flags = 0x%x\n",
				action.sa_handler, SigNames.get_name(signo), action.sa_flags
			);
		}
	}
	is_installed = TRUE;

	dprintf( D_FULLDEBUG, "}\n" );
}
