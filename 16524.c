instance_handler(vector_t *strvec)
{
	if (!strvec)
		return;

	if (!reload) {
		if (!global_data->instance_name) {
			global_data->instance_name = set_value(strvec);
			use_pid_dir = true;
		}
		else
			report_config_error(CONFIG_GENERAL_ERROR, "Duplicate instance definition %s - ignoring", FMT_STR_VSLOT(strvec, 1));
	}
}
