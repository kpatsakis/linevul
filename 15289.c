void logerr(const char *msg) {
	if (!arg_debug)
		return;

	openlog("firejail", LOG_NDELAY | LOG_PID, LOG_USER);
	syslog(LOG_ERR, "%s\n", msg);
	closelog();
}
