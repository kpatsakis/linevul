process(struct magic_set *ms, const char *inname, int wid)
{
	const char *type;
	int std_in = strcmp(inname, "-") == 0;

	if (wid > 0 && !bflag) {
		(void)printf("%s", std_in ? "/dev/stdin" : inname);
		if (nulsep)
			(void)putc('\0', stdout);
		(void)printf("%s", separator);
		(void)printf("%*s ",
		    (int) (nopad ? 0 : (wid - file_mbswidth(inname))), "");
	}

	type = magic_file(ms, std_in ? NULL : inname);
	if (type == NULL) {
		(void)printf("ERROR: %s\n", magic_error(ms));
		return 1;
	} else {
		(void)printf("%s\n", type);
		return 0;
	}
}
