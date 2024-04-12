usage(void)
{
	const char	*p;

	p = lafe_getprogname();

	fprintf(stderr, "Brief Usage:\n");
	fprintf(stderr, "  List:    %s -it < archive\n", p);
	fprintf(stderr, "  Extract: %s -i < archive\n", p);
	fprintf(stderr, "  Create:  %s -o < filenames > archive\n", p);
	fprintf(stderr, "  Help:    %s --help\n", p);
	exit(1);
}
