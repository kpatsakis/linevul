cmd_http_expect(CMD_ARGS)
{
	struct http *hp;
	const char *lhs;
	char *cmp;
	const char *rhs;

	(void)cmd;
	(void)vl;
	CAST_OBJ_NOTNULL(hp, priv, HTTP_MAGIC);
	assert(!strcmp(av[0], "expect"));
	av++;

	AN(av[0]);
	AN(av[1]);
	AN(av[2]);
	AZ(av[3]);
	lhs = cmd_var_resolve(hp, av[0]);
	cmp = av[1];
	rhs = cmd_var_resolve(hp, av[2]);
	if (!strcmp(cmp, "==")) {
		if (strcmp(lhs, rhs))
			vtc_log(hp->vl, 0, "EXPECT %s (%s) %s %s (%s) failed",
			    av[0], lhs, av[1], av[2], rhs);
		else
			vtc_log(hp->vl, 4, "EXPECT %s (%s) %s %s (%s) match",
			    av[0], lhs, av[1], av[2], rhs);
	} else if (!strcmp(cmp, "!=")) {
		if (!strcmp(lhs, rhs))
			vtc_log(hp->vl, 0, "EXPECT %s (%s) %s %s (%s) failed",
			    av[0], lhs, av[1], av[2], rhs);
		else
			vtc_log(hp->vl, 4, "EXPECT %s (%s) %s %s (%s) match",
			    av[0], lhs, av[1], av[2], rhs);
	} else {
		vtc_log(hp->vl, 0,
		    "EXPECT %s (%s) %s %s (%s) test not implemented",
		    av[0], lhs, av[1], av[2], rhs);
	}
}
