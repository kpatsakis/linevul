CStarter::CStarter()
{
	Execute = NULL;
	orig_cwd = NULL;
	is_gridshell = false;
	ShuttingDown = FALSE;
	jic = NULL;
	jobUniverse = CONDOR_UNIVERSE_VANILLA;
	pre_script = NULL;
	post_script = NULL;
	starter_stdin_fd = -1;
	starter_stdout_fd = -1;
	starter_stderr_fd = -1;
	deferral_tid = -1;
	suspended = false;
	m_privsep_helper = NULL;
	m_configured = false;
	m_job_environment_is_ready = false;
	m_all_jobs_done = false;
	m_deferred_job_update = false;
}
