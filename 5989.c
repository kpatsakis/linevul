int mpol_parse_str(char *str, struct mempolicy **mpol, int no_context)
{
	struct mempolicy *new = NULL;
	unsigned short mode;
	unsigned short uninitialized_var(mode_flags);
	nodemask_t nodes;
	char *nodelist = strchr(str, ':');
	char *flags = strchr(str, '=');
	int err = 1;

	if (nodelist) {
		/* NUL-terminate mode or flags string */
		*nodelist++ = '\0';
		if (nodelist_parse(nodelist, nodes))
			goto out;
		if (!nodes_subset(nodes, node_states[N_HIGH_MEMORY]))
			goto out;
	} else
		nodes_clear(nodes);

	if (flags)
		*flags++ = '\0';	/* terminate mode string */

	for (mode = 0; mode <= MPOL_LOCAL; mode++) {
		if (!strcmp(str, policy_modes[mode])) {
			break;
		}
	}
	if (mode > MPOL_LOCAL)
		goto out;

	switch (mode) {
	case MPOL_PREFERRED:
		/*
		 * Insist on a nodelist of one node only
		 */
		if (nodelist) {
			char *rest = nodelist;
			while (isdigit(*rest))
				rest++;
			if (*rest)
				goto out;
		}
		break;
	case MPOL_INTERLEAVE:
		/*
		 * Default to online nodes with memory if no nodelist
		 */
		if (!nodelist)
			nodes = node_states[N_HIGH_MEMORY];
		break;
	case MPOL_LOCAL:
		/*
		 * Don't allow a nodelist;  mpol_new() checks flags
		 */
		if (nodelist)
			goto out;
		mode = MPOL_PREFERRED;
		break;
	case MPOL_DEFAULT:
		/*
		 * Insist on a empty nodelist
		 */
		if (!nodelist)
			err = 0;
		goto out;
	case MPOL_BIND:
		/*
		 * Insist on a nodelist
		 */
		if (!nodelist)
			goto out;
	}

	mode_flags = 0;
	if (flags) {
		/*
		 * Currently, we only support two mutually exclusive
		 * mode flags.
		 */
		if (!strcmp(flags, "static"))
			mode_flags |= MPOL_F_STATIC_NODES;
		else if (!strcmp(flags, "relative"))
			mode_flags |= MPOL_F_RELATIVE_NODES;
		else
			goto out;
	}

	new = mpol_new(mode, mode_flags, &nodes);
	if (IS_ERR(new))
		goto out;

	if (no_context) {
		/* save for contextualization */
		new->w.user_nodemask = nodes;
	} else {
		int ret;
		NODEMASK_SCRATCH(scratch);
		if (scratch) {
			task_lock(current);
			ret = mpol_set_nodemask(new, &nodes, scratch);
			task_unlock(current);
		} else
			ret = -ENOMEM;
		NODEMASK_SCRATCH_FREE(scratch);
		if (ret) {
			mpol_put(new);
			goto out;
		}
	}
	err = 0;

out:
	/* Restore string for error message */
	if (nodelist)
		*--nodelist = ':';
	if (flags)
		*--flags = '=';
	if (!err)
		*mpol = new;
	return err;
}
