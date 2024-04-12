void invalid_filename(const char *fname) {
	EUID_ASSERT();
	assert(fname);
	const char *ptr = fname;

	if (arg_debug_check_filename)
		printf("Checking filename %s\n", fname);

	if (strncmp(ptr, "${HOME}", 7) == 0)
		ptr = fname + 7;
	else if (strncmp(ptr, "${PATH}", 7) == 0)
		ptr = fname + 7;
	else if (strcmp(fname, "${DOWNLOADS}") == 0)
		return;

	int len = strlen(ptr);
	if (strcspn(ptr, "\\&!?\"'<>%^(){}[];,") != (size_t)len) {
		fprintf(stderr, "Error: \"%s\" is an invalid filename\n", ptr);
		exit(1);
	}
}
