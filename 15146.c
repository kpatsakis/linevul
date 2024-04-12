check_follow_cname(char **namep, const char *cname)
{
	int i;
	struct allowed_cname *rule;

	if (*cname == '\0' || options.num_permitted_cnames == 0 ||
	    strcmp(*namep, cname) == 0)
		return 0;
	if (options.canonicalize_hostname == SSH_CANONICALISE_NO)
		return 0;
	/*
	 * Don't attempt to canonicalize names that will be interpreted by
	 * a proxy unless the user specifically requests so.
	 */
	if (!option_clear_or_none(options.proxy_command) &&
	    options.canonicalize_hostname != SSH_CANONICALISE_ALWAYS)
		return 0;
	debug3("%s: check \"%s\" CNAME \"%s\"", __func__, *namep, cname);
	for (i = 0; i < options.num_permitted_cnames; i++) {
		rule = options.permitted_cnames + i;
		if (match_pattern_list(*namep, rule->source_list, 1) != 1 ||
		    match_pattern_list(cname, rule->target_list, 1) != 1)
			continue;
		verbose("Canonicalized DNS aliased hostname "
		    "\"%s\" => \"%s\"", *namep, cname);
		free(*namep);
		*namep = xstrdup(cname);
		return 1;
	}
	return 0;
}
