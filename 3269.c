static bool read_access(const char * filename ) {
	return thisRemoteResource->allowRemoteReadFileAccess( filename );
}
