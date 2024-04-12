vrrp_state_handler(vector_t *strvec)
{
	char *str = strvec_slot(strvec, 1);
	vrrp_t *vrrp = LIST_TAIL_DATA(vrrp_data->vrrp);

	if (!strcmp(str, "MASTER"))
		vrrp->wantstate = VRRP_STATE_MAST;
	else if (!strcmp(str, "BACKUP"))
	{
		if (vrrp->wantstate == VRRP_STATE_MAST)
			report_config_error(CONFIG_GENERAL_ERROR, "(%s) state previously set as MASTER - ignoring BACKUP", vrrp->iname);
		else
			vrrp->wantstate = VRRP_STATE_BACK;
	}
	else {
		report_config_error(CONFIG_GENERAL_ERROR,"(%s) unknown state '%s', defaulting to BACKUP", vrrp->iname, str);
		vrrp->wantstate = VRRP_STATE_BACK;
	}
}
