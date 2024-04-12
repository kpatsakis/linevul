vrrp_native_ipv6_handler(__attribute__((unused)) vector_t *strvec)
{
	vrrp_t *vrrp = LIST_TAIL_DATA(vrrp_data->vrrp);

	if (vrrp->family == AF_INET) {
		report_config_error(CONFIG_GENERAL_ERROR,"(%s) Cannot specify native_ipv6 with IPv4 addresses", vrrp->iname);
		return;
	}

	vrrp->family = AF_INET6;
	vrrp->version = VRRP_VERSION_3;
}
