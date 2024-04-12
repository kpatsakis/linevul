struct in6_addr *ndp_msg_opt_route_prefix(struct ndp_msg *msg, int offset)
{
	static struct in6_addr prefix;
	struct __nd_opt_route_info *ri =
			ndp_msg_payload_opts_offset(msg, offset);

	memset(&prefix, 0, sizeof(prefix));
	memcpy(&prefix, &ri->nd_opt_ri_prefix, (ri->nd_opt_ri_len - 1) << 3);
	return &prefix;
}
