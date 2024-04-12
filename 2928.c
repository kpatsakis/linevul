static char *ask_new_field(struct chfn_control *ctl, const char *question,
			   char *def_val)
{
	int len;
	char *ans;
	char buf[MAX_FIELD_SIZE + 2];

	if (!def_val)
		def_val = "";
	while (true) {
		printf("%s [%s]: ", question, def_val);
		__fpurge(stdin);
		if (fgets(buf, sizeof(buf), stdin) == NULL)
			errx(EXIT_FAILURE, _("Aborted."));
		ans = buf;
		/* remove white spaces from string end */
		ltrim_whitespace((unsigned char *) ans);
		len = rtrim_whitespace((unsigned char *) ans);
		if (len == 0)
			return xstrdup(def_val);
		if (!strcasecmp(ans, "none")) {
			ctl->changed = 1;
			return xstrdup("");
		}
		if (check_gecos_string(question, ans) >= 0)
			break;
	}
	ctl->changed = 1;
	return xstrdup(ans);
}
