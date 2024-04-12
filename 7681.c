static void sandbox_handler(int sig){
	usleep(10000); // don't race to print a message
	fmessage("\nChild received signal %d, shutting down the sandbox...\n", sig);

	kill(-1, SIGTERM);
	sleep(1);

	if (monitored_pid) {
		int monsec = 9;
		char *monfile;
		if (asprintf(&monfile, "/proc/%d/cmdline", monitored_pid) == -1)
			errExit("asprintf");
		while (monsec) {
			FILE *fp = fopen(monfile, "r");
			if (!fp)
				break;

			char c;
			size_t count = fread(&c, 1, 1, fp);
			fclose(fp);
			if (count == 0)
				break;

			if (arg_debug)
				printf("Waiting on PID %d to finish\n", monitored_pid);
			sleep(1);
			monsec--;
		}
		free(monfile);
	}

	kill(-1, SIGKILL);
	flush_stdin();

	exit(sig);
}
