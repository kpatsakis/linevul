unsigned FAST_FUNC udhcp_option_idx(const char *name, const char *option_strings)
{
	int n = index_in_strings(option_strings, name);
	if (n >= 0)
		return n;

	{
		char *buf, *d;
		const char *s;

		s = option_strings;
		while (*s)
			s += strlen(s) + 1;

		d = buf = xzalloc(s - option_strings);
		s = option_strings;
		while (!(*s == '\0' && s[1] == '\0')) {
			*d++ = (*s == '\0' ? ' ' : *s);
			s++;
		}
		bb_error_msg_and_die("unknown option '%s', known options: %s", name, buf);
	}
}
