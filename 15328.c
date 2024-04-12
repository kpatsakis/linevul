void CL_UpdateServerInfo( int n ) {
	if ( !cl_pinglist[n].adr.port ) {
		return;
	}

	CL_SetServerInfoByAddress( cl_pinglist[n].adr, cl_pinglist[n].info, cl_pinglist[n].time );
}
