int udpv6_offload_init(void)
{
	return inet6_add_offload(&udpv6_offload, IPPROTO_UDP);
}
