void logsignal(int s) {
	if (!arg_debug)
		return;

	openlog("firejail", LOG_NDELAY | LOG_PID, LOG_USER);
	syslog(LOG_INFO, "Signal %d caught", s);
	closelog();
}
