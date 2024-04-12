static_track_group_handler(vector_t *strvec)
{
	element e;
	static_track_group_t *tg;
	char* gname;

	if (!strvec)
		return;

	if (vector_count(strvec) != 2) {
		report_config_error(CONFIG_GENERAL_ERROR, "track_group must have a name - skipping");
		skip_block(true);
		return;
	}

	gname = strvec_slot(strvec, 1);

	/* check group doesn't already exist */
	LIST_FOREACH(vrrp_data->static_track_groups, tg, e) {
		if (!strcmp(gname,tg->gname)) {
			report_config_error(CONFIG_GENERAL_ERROR, "track_group %s already defined", gname);
			skip_block(true);
			return;
		}
	}

	alloc_static_track_group(gname);
}
