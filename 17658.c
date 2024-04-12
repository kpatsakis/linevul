is_myproxy_file( const char *name )
{
	int cluster, proc;

	int rc = sscanf( name, "mpp.%d.%d", &cluster, &proc );
	if ( rc != 2 ) {
		return FALSE;
	}
	return proc_exists( cluster, proc );
}
