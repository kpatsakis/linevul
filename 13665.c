process_running(const char *pid_file)
{
	FILE *pidfile = fopen(pid_file, "r");
	pid_t pid = 0;
	int ret;

	/* No pidfile */
	if (!pidfile)
		return 0;

	ret = fscanf(pidfile, "%d", &pid);
	fclose(pidfile);
	if (ret != 1) {
		log_message(LOG_INFO, "Error reading pid file %s", pid_file);
		pid = 0;
		pidfile_rm(pid_file);
	}

	/* What should we return - we don't know if it is running or not. */
	if (!pid)
		return 1;

	/* If no process is attached to pidfile, remove it */
	if (kill(pid, 0)) {
		log_message(LOG_INFO, "Remove a zombie pid file %s", pid_file);
		pidfile_rm(pid_file);
		return 0;
	}

	return 1;
}
