void notify_other(int fd) {
	FILE* stream;
	int newfd = dup(fd);
	if (newfd == -1)
		errExit("dup");
	stream = fdopen(newfd, "w");
	fprintf(stream, "arg_noroot=%d\n", arg_noroot);
	fflush(stream);
	fclose(stream);
}
