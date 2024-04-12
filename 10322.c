nm_ip4_config_get_ifindex (const NMIP4Config *config)
{
	return NM_IP4_CONFIG_GET_PRIVATE (config)->ifindex;
}
