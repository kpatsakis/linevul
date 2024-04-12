void notify_other(int fd) {
	FILE* stream;
	int newfd = dup(fd);
	if (newfd == -1)
		errExit("dup");
	stream = fdopen(newfd, "w");
	fprintf(stream, "%u\n", getpid());
	fflush(stream);
	fclose(stream);
}
