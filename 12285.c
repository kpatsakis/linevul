void CL_CheckTimeout( void ) {
	if ( ( !CL_CheckPaused() || !sv_paused->integer ) 
		&& clc.state >= CA_CONNECTED && clc.state != CA_CINEMATIC
	    && cls.realtime - clc.lastPacketTime > cl_timeout->value*1000) {
		if (++cl.timeoutcount > 5) {	// timeoutcount saves debugger
			Com_Printf ("\nServer connection timed out.\n");
			CL_Disconnect( qtrue );
			return;
		}
	} else {
		cl.timeoutcount = 0;
	}
}
