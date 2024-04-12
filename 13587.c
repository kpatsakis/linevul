BaseShadow::terminateJob( update_style_t kind ) // has a default argument of US_NORMAL
{
	int reason;
	bool signaled;
	MyString str;

	if( ! jobAd ) {
		dprintf( D_ALWAYS, "In terminateJob() w/ NULL JobAd!" );
	}

	/* The first thing we do is record that we are in a termination pending
		state. */
	if (kind == US_NORMAL) {
		str.sprintf("%s = TRUE", ATTR_TERMINATION_PENDING);
		jobAd->Insert(str.Value());
	}

	if (kind == US_TERMINATE_PENDING) {

		int exited_by_signal = FALSE;
		int exit_signal = 0;
		int exit_code = 0;

		getJobAdExitedBySignal(jobAd, exited_by_signal);
		if (exited_by_signal == TRUE) {
			getJobAdExitSignal(jobAd, exit_signal);
		} else {
			getJobAdExitCode(jobAd, exit_code);
		}

		if (exited_by_signal == TRUE) {
			reason = JOB_COREDUMPED;
			str.sprintf("%s = \"%s\"", ATTR_JOB_CORE_FILENAME, core_file_name);
			jobAd->Insert(str.Value());
		} else {
			reason = JOB_EXITED;
		}

		dprintf( D_ALWAYS, "Job %d.%d terminated: %s %d\n",
	 		getCluster(), getProc(), 
	 		exited_by_signal? "killed by signal" : "exited with status",
	 		exited_by_signal ? exit_signal : exit_code );
		
		logTerminateEvent( reason, kind );

		emailTerminateEvent( reason, kind );

		DC_Exit( reason );
	}


	cleanUp();

	reason = getExitReason();
	signaled = exitedBySignal();

	/* also store the corefilename into the jobad so we can recover this 
		during a termination pending scenario. */
	if( reason == JOB_COREDUMPED ) {
		str.sprintf("%s = \"%s\"", ATTR_JOB_CORE_FILENAME, getCoreName());
		jobAd->Insert(str.Value());
	}

    int last_ckpt_time = 0;
    jobAd->LookupInteger(ATTR_LAST_CKPT_TIME, last_ckpt_time);
    int current_start_time = 0;
    jobAd->LookupInteger(ATTR_JOB_CURRENT_START_DATE, current_start_time);
    int int_value = (last_ckpt_time > current_start_time) ?
                        last_ckpt_time : current_start_time;

    if( int_value > 0 ) {
        int job_committed_time = 0;
        jobAd->LookupInteger(ATTR_JOB_COMMITTED_TIME, job_committed_time);
		int delta = (int)time(NULL) - int_value;
        job_committed_time += delta;
        jobAd->Assign(ATTR_JOB_COMMITTED_TIME, job_committed_time);

		float slot_weight = 1;
		jobAd->LookupFloat(ATTR_JOB_MACHINE_ATTR_SLOT_WEIGHT0, slot_weight);
		float slot_time = 0;
		jobAd->LookupFloat(ATTR_COMMITTED_SLOT_TIME, slot_time);
		slot_time += slot_weight * delta;
		jobAd->Assign(ATTR_COMMITTED_SLOT_TIME, slot_time);
    }

	CommitSuspensionTime(jobAd);

    if (m_num_cleanup_retries < 1 &&
        param_boolean("SHADOW_TEST_JOB_CLEANUP_RETRY", false)) {
		dprintf( D_ALWAYS,
				 "Testing Failure to perform final update to job queue!\n");
		retryJobCleanup();
		return;
    }
	if( !updateJobInQueue(U_TERMINATE) ) {
		dprintf( D_ALWAYS, 
				 "Failed to perform final update to job queue!\n");
		retryJobCleanup();
		return;
	}


	dprintf( D_ALWAYS, "Job %d.%d terminated: %s %d\n",
	 	getCluster(), getProc(), 
	 	signaled ? "killed by signal" : "exited with status",
	 	signaled ? exitSignal() : exitCode() );

	logTerminateEvent( reason );

	emailTerminateEvent( reason );

	if( reason == JOB_EXITED && claimIsClosing() ) {
		dprintf(D_FULLDEBUG,"Startd is closing claim, so no more jobs can be run on it.\n");
		reason = JOB_EXITED_AND_CLAIM_CLOSING;
	}

	if( recycleShadow(reason) ) {
		return;
	}

	DC_Exit( reason );
}
