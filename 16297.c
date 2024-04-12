static_track_group_group_handler(vector_t *strvec)
{
	static_track_group_t *tgroup = LIST_TAIL_DATA(vrrp_data->static_track_groups);

	if (tgroup->iname) {
		report_config_error(CONFIG_GENERAL_ERROR, "Group list already specified for sync group %s", tgroup->gname);
		skip_block(true);
		return;
	}

	tgroup->iname = read_value_block(strvec);

	if (!tgroup->iname)
		report_config_error(CONFIG_GENERAL_ERROR, "Warning - track group %s has empty group block", tgroup->gname);
}
