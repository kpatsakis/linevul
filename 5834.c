fill_attributes()
{
		/* There are a few attributes that specify what platform we're
		   on that we want to insert values for even if they're not
		   defined in the config sources.  These are ARCH and OPSYS,
		   which we compute with the sysapi_condor_arch() and sysapi_opsys()
		   functions.  We also insert the subsystem here.  Moved all
		   the domain stuff to check_domain_attributes() on
		   10/20.  Also, since this is called before we read in any
		   config sources, there's no reason to check to see if any of
		   these are already defined.  -Derek Wright
		   Amended -Pete Keller 06/01/99 */

	const char *tmp;
	MyString val;

	if( (tmp = sysapi_condor_arch()) != NULL ) {
		insert( "ARCH", tmp, ConfigTab, TABLESIZE );
		extra_info->AddInternalParam("ARCH");
	}

	if( (tmp = sysapi_uname_arch()) != NULL ) {
		insert( "UNAME_ARCH", tmp, ConfigTab, TABLESIZE );
		extra_info->AddInternalParam("UNAME_ARCH");
	}

	if( (tmp = sysapi_opsys()) != NULL ) {
		insert( "OPSYS", tmp, ConfigTab, TABLESIZE );
		extra_info->AddInternalParam("OPSYS");

		int ver = sysapi_opsys_version();
		if (ver > 0) {
			val.sprintf("%d", ver);
			insert( "OPSYSVER", val.Value(), ConfigTab, TABLESIZE );
			extra_info->AddInternalParam("OPSYSVER");
		}
	}

	if( (tmp = sysapi_opsys_versioned()) != NULL ) {
		insert( "OPSYS_AND_VER", tmp, ConfigTab, TABLESIZE );
		extra_info->AddInternalParam("OPSYS_AND_VER");
	}

	if( (tmp = sysapi_uname_opsys()) != NULL ) {
		insert( "UNAME_OPSYS", tmp, ConfigTab, TABLESIZE );
		extra_info->AddInternalParam("UNAME_OPSYS");
	}

	insert( "SUBSYSTEM", get_mySubSystem()->getName(), ConfigTab, TABLESIZE );
	extra_info->AddInternalParam("SUBSYSTEM");

	val.sprintf("%d",sysapi_phys_memory_raw_no_param());
	insert( "DETECTED_MEMORY", val.Value(), ConfigTab, TABLESIZE );
	extra_info->AddInternalParam("DETECTED_MEMORY");

	int num_cpus=0;
	int num_hyperthread_cpus=0;
	sysapi_ncpus_raw_no_param(&num_cpus,&num_hyperthread_cpus);

	val.sprintf("%d",num_hyperthread_cpus);
	insert( "DETECTED_CORES", val.Value(), ConfigTab, TABLESIZE );
	extra_info->AddInternalParam("DETECTED_CORES");
}
