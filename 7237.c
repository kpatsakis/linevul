nm_ip4_config_new (int ifindex)
{
	g_return_val_if_fail (ifindex >= -1, NULL);
	return (NMIP4Config *) g_object_new (NM_TYPE_IP4_CONFIG,
	                                     NM_IP4_CONFIG_IFINDEX, ifindex,
	                                     NULL);
}
