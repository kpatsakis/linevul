garp_group_interface_handler(vector_t *strvec)
{
	interface_t *ifp = if_get_by_ifname(strvec_slot(strvec, 1), IF_CREATE_IF_DYNAMIC);
	if (!ifp) {
		report_config_error(CONFIG_GENERAL_ERROR, "WARNING - interface %s specified for garp_group doesn't exist", FMT_STR_VSLOT(strvec, 1));
		return;
	}

	if (ifp->garp_delay) {
		report_config_error(CONFIG_GENERAL_ERROR, "garp_group already specified for %s - ignoring", FMT_STR_VSLOT(strvec, 1));
		return;
	}

#ifdef _HAVE_VRRP_VMAC_
	/* We cannot have a group on a vmac interface */
	if (ifp->vmac_type) {
		report_config_error(CONFIG_GENERAL_ERROR, "Cannot specify garp_delay on a vmac (%s) - ignoring", ifp->ifname);
		return;
	}
#endif
	ifp->garp_delay = LIST_TAIL_DATA(garp_delay);
}
