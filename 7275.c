cmd_http_loop(CMD_ARGS)
{
	struct http *hp;
	unsigned n, m;
	char *s;

	CAST_OBJ_NOTNULL(hp, priv, HTTP_MAGIC);
	AN(av[1]);
	AN(av[2]);
	AZ(av[3]);
	n = strtoul(av[1], NULL, 0);
	for (m = 1 ; m <= n; m++) {
		vtc_log(vl, 4, "Loop #%u", m);
		s = strdup(av[2]);
		AN(s);
		parse_string(s, cmd, hp, vl);
	}
}
