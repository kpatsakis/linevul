vrrp_vscript_user_handler(vector_t *strvec)
{
	vrrp_script_t *vscript = LIST_TAIL_DATA(vrrp_data->vrrp_script);

	if (set_script_uid_gid(strvec, 1, &vscript->script.uid, &vscript->script.gid)) {
		report_config_error(CONFIG_GENERAL_ERROR, "Unable to set uid/gid for script %s", cmd_str(&vscript->script));
		remove_script = true;
	}
	else {
		remove_script = false;
		script_user_set = true;
	}
}
