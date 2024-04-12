int pseudo_get_file_info_new( const char *logical_name, char *&actual_url )
{
	MyString remap_list;
	MyString	split_dir;
	MyString	split_file;
	MyString	full_path;
	MyString	remap;
	MyString urlbuf;
	const char	*method;

	dprintf( D_SYSCALLS, "\tlogical_name = \"%s\"\n", logical_name );

	ASSERT( actual_url == NULL );

	/* The incoming logical name might be a simple, relative, or complete path */
	/* We need to examine both the full path and the simple name. */

	filename_split( logical_name, split_dir, split_file );
	complete_path( logical_name, full_path );

	/* Any name comparisons must check the logical name, the simple name, and the full path */

	if(Shadow->getJobAd()->LookupString(ATTR_FILE_REMAPS,remap_list) &&
	  (filename_remap_find( remap_list.Value(), logical_name, remap ) ||
	   filename_remap_find( remap_list.Value(), split_file.Value(), remap ) ||
	   filename_remap_find( remap_list.Value(), full_path.Value(), remap ))) {

		dprintf(D_SYSCALLS,"\tremapped to: %s\n",remap.Value());

		/* If the remap is a full URL, return right away */
		/* Otherwise, continue processing */

		if(strchr(remap.Value(),':')) {
			dprintf(D_SYSCALLS,"\tremap is complete url\n");
			actual_url = strdup(remap.Value());
			return 0;
		} else {
			dprintf(D_SYSCALLS,"\tremap is simple file\n");
			complete_path( remap.Value(), full_path );
		}
	} else {
		dprintf(D_SYSCALLS,"\tnot remapped\n");
	}

	dprintf( D_SYSCALLS,"\tfull_path = \"%s\"\n", full_path.Value() );

	/* Now, we have a full pathname. */
	/* Figure out what url modifiers to slap on it. */

#ifdef HPUX
	/* I have no idea why this is happening, but I have seen it happen many
	 * times on the HPUX version, so here is a quick hack -Todd 5/19/95 */
	if ( full_path == "/usr/lib/nls////strerror.cat" )
		full_path = "/usr/lib/nls/C/strerror.cat\0";
#endif

	if( use_special_access(full_path.Value()) ) {
		method = "special";
	} else if( use_local_access(full_path.Value()) ) {
		method = "local";
	} else if( access_via_afs(full_path.Value()) ) {
		method = "local";
	} else if( access_via_nfs(full_path.Value()) ) {
		method = "local";
	} else {
		method = "remote";
	}

	if( use_fetch(method,full_path.Value()) ) {
		urlbuf += "fetch:";
	}

	if( use_compress(method,full_path.Value()) ) {
		urlbuf += "compress:";
	}

	append_buffer_info(urlbuf,method,full_path.Value());

	if( use_append(method,full_path.Value()) ) {
		urlbuf += "append:";
	}

	urlbuf += method;
	urlbuf += ":";
	urlbuf += full_path;
	actual_url = strdup(urlbuf.Value());

	dprintf(D_SYSCALLS,"\tactual_url: %s\n",actual_url);

	return 0;
}
