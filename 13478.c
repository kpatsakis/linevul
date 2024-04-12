condor_net_remap_config( bool force_param )
{
    char *str = NULL;
	if( ! force_param && getenv("NET_REMAP_ENABLE") ) {
			/*
			  this stuff is already set.  unless the caller is forcing
			  us to call param() again (e.g. the master is trying to
			  re-bind() if the GCB broker is down and it's got a list
			  to try) we should return immediately and leave our
			  environment alone.  this way, the master can choose what
			  GCB broker to use for itself and all its children, even
			  if there's a list and we're using $RANDOM_CHOICE().
			*/
		return;
	}
		
		/*
		  this method is only called if we're enabling a network remap
		  service.  if we do, we always need to force condor to bind()
		  to all interfaces (INADDR_ANY).  since we don't want to rely
		  on users to set this themselves to get GCB working, we'll
		  set it automatically.  the only harm of setting this is that
		  we need Condor to automatically handle hostallow stuff for
		  "localhost", or users need to add localhost to their
		  hostallow settings as appropriate.  we can't rely on the
		  later, and the former only works on some platforms.
		  luckily, the automatic localhost stuff works on all
		  platforms where GCB works (linux, and we hope, solaris), so
		  it's safe to turn this on whenever we're using GCB
		*/
	insert( "BIND_ALL_INTERFACES", "TRUE", ConfigTab, TABLESIZE );
	extra_info->AddInternalParam("BIND_ALL_INTERFACES");

    SetEnv( "NET_REMAP_ENABLE", "true");
    str = param("NET_REMAP_SERVICE");
    if (str) {
        if (!strcasecmp(str, "GCB")) {
            SetEnv( "GCB_ENABLE", "true" );
            free(str);
            str = NULL;
            if( (str = param("NET_REMAP_INAGENT")) ) {
				const char *next_broker;
				StringList all_brokers( str );
				StringList working_brokers;

				all_brokers.rewind();
				while ( (next_broker = all_brokers.next()) ) {
					int rc = 0;

#if HAVE_EXT_GCB
					int num_slots = 0;	/* only used w/HAVE_EXT_GCB */
					rc = GCB_broker_query( next_broker,
										   GCB_DATA_QUERY_FREE_SOCKS,
										   &num_slots );
#endif
					if ( rc == 0 ) {
						working_brokers.append( next_broker );
					}
				}

				if ( working_brokers.number() > 0 ) {
					int rand_entry = (get_random_int() % working_brokers.number()) + 1;
					int i = 0;
					working_brokers.rewind();
					while ( (i < rand_entry) &&
							(next_broker=working_brokers.next()) ) {
						i++;
					}

					dprintf( D_FULLDEBUG,"Using GCB broker %s\n",next_broker );
					SetEnv( "GCB_INAGENT", next_broker );
				} else {
					dprintf( D_ALWAYS,"No usable GCB brokers were found. "
							 "Setting GCB_INAGENT=%s\n",
							 CONDOR_GCB_INVALID_BROKER );
					SetEnv( "GCB_INAGENT", CONDOR_GCB_INVALID_BROKER );
				}
				free( str );
                str = NULL;
            }
            if( (str = param("NET_REMAP_ROUTE")) ) {
                SetEnv( "GCB_ROUTE", str );
				free( str );
                str = NULL;
            }
        } else if (!strcasecmp(str, "DPF")) {
            SetEnv( "DPF_ENABLE", "true" );
            free(str);
            str = NULL;
            if( (str = param("NET_REMAP_INAGENT")) ) {
                SetEnv( "DPF_INAGENT", str );
				free(str);
				str = NULL;
            }
            if( (str = param("NET_REMAP_ROUTE")) ) {
                SetEnv( "DPF_ROUTE", str );
				free(str);
				str = NULL;
            }
        }
    }
}
