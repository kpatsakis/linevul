check_domain_attributes()
{
		/* Make sure the FILESYSTEM_DOMAIN and UID_DOMAIN attributes
		   are set to something reasonable.  If they're not already
		   defined, we default to our own full hostname.  Moved this
		   to its own function so we're sure we have our full hostname
		   by the time we call this. -Derek Wright 10/20/98 */

	char *uid_domain, *filesys_domain;

	filesys_domain = param("FILESYSTEM_DOMAIN");
	if( !filesys_domain ) {
		insert( "FILESYSTEM_DOMAIN", get_local_fqdn().Value(), 
				ConfigTab, TABLESIZE );
		extra_info->AddInternalParam("FILESYSTEM_DOMAIN");
	} else {
		free( filesys_domain );
	}

	uid_domain = param("UID_DOMAIN");
	if( !uid_domain ) {
		insert( "UID_DOMAIN", get_local_fqdn().Value(), 
				ConfigTab, TABLESIZE );
		extra_info->AddInternalParam("UID_DOMAIN");
	} else {
		free( uid_domain );
	}
}
