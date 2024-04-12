CStarter::RemoteHold( int )
{
	if( jic ) {
		jic->gotHold();
	}
	if ( this->Hold( ) ) {
		dprintf( D_FULLDEBUG, "Got Hold when no jobs running\n" );
		this->allJobsDone();
		return ( true );
	}	
	return ( false );
}
