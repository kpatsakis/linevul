sysEvent_t  Com_GetEvent( void ) {
	if ( com_pushedEventsHead > com_pushedEventsTail ) {
		com_pushedEventsTail++;
		return com_pushedEvents[ ( com_pushedEventsTail - 1 ) & ( MAX_PUSHED_EVENTS - 1 ) ];
	}
	return Com_GetRealEvent();
}
