void flush_stdin(void) {
	if (isatty(STDIN_FILENO)) {
		int cnt = 0;
		ioctl(STDIN_FILENO, FIONREAD, &cnt);
		if (cnt) {
			if (!arg_quiet)
				printf("Warning: removing %d bytes from stdin\n", cnt);
			ioctl(STDIN_FILENO, TCFLSH, TCIFLUSH);
		}
	}
}
