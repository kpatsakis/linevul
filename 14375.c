int Com_EventLoop( void ) {
	sysEvent_t ev;
	netadr_t evFrom;
	byte bufData[MAX_MSGLEN];
	msg_t buf;

	MSG_Init( &buf, bufData, sizeof( bufData ) );

	while ( 1 ) {
		ev = Com_GetEvent();

		if ( ev.evType == SE_NONE ) {
			while ( NET_GetLoopPacket( NS_CLIENT, &evFrom, &buf ) ) {
				CL_PacketEvent( evFrom, &buf );
			}

			while ( NET_GetLoopPacket( NS_SERVER, &evFrom, &buf ) ) {
				if ( com_sv_running->integer ) {
					Com_RunAndTimeServerPacket( &evFrom, &buf );
				}
			}

			return ev.evTime;
		}


		switch(ev.evType)
		{
			case SE_KEY:
				CL_KeyEvent( ev.evValue, ev.evValue2, ev.evTime );
			break;
			case SE_CHAR:
				CL_CharEvent( ev.evValue );
			break;
			case SE_MOUSE:
				CL_MouseEvent( ev.evValue, ev.evValue2, ev.evTime );
			break;
			case SE_JOYSTICK_AXIS:
				CL_JoystickEvent( ev.evValue, ev.evValue2, ev.evTime );
			break;
			case SE_CONSOLE:
				Cbuf_AddText( (char *)ev.evPtr );
				Cbuf_AddText( "\n" );
			break;
			default:
				Com_Error( ERR_FATAL, "Com_EventLoop: bad event type %i", ev.evType );
			break;
		}

		if ( ev.evPtr ) {
			Z_Free( ev.evPtr );
		}
	}

	return 0;   // never reached
}
