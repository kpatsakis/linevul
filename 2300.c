BaseShadow::logEvictEvent( int exitReason )
{
	struct rusage run_remote_rusage;
	memset( &run_remote_rusage, 0, sizeof(struct rusage) );

	run_remote_rusage = getRUsage();

	switch( exitReason ) {
	case JOB_CKPTED:
	case JOB_NOT_CKPTED:
	case JOB_KILLED:
		break;
	default:
		dprintf( D_ALWAYS, 
				 "logEvictEvent with unknown reason (%d), aborting\n",
				 exitReason ); 
		return;
	}

	JobEvictedEvent event;
	event.checkpointed = (exitReason == JOB_CKPTED);
	
			
	event.run_remote_rusage = run_remote_rusage;
	
		/*
		  we want to log the events from the perspective of the user
		  job, so if the shadow *sent* the bytes, then that means the
		  user job *received* the bytes
		*/
	event.recvd_bytes = bytesSent();
	event.sent_bytes = bytesReceived();
	
	if (!uLog.writeEvent (&event,jobAd)) {
		dprintf (D_ALWAYS, "Unable to log ULOG_JOB_EVICTED event\n");
	}
}
