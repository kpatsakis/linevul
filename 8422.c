static void save_nonewprivs(void) {
	if (arg_nonewprivs == 0)
		return;

	FILE *fp = fopen(RUN_NONEWPRIVS_CFG, "wxe");
	if (fp) {
		fprintf(fp, "\n");
		SET_PERMS_STREAM(fp, 0, 0, 0644); // assume mode 0644
		fclose(fp);
	}
	else {
		fprintf(stderr, "Error: cannot save nonewprivs state\n");
		exit(1);
	}
}
