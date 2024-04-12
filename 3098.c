size_t bgp_packet_mpattr_prefix_size(afi_t afi, safi_t safi, struct prefix *p)
{
	int size = PSIZE(p->prefixlen);
	if (safi == SAFI_MPLS_VPN)
		size += 88;
	else if (afi == AFI_L2VPN && safi == SAFI_EVPN)
		size += 232; // TODO: Maximum possible for type-2, type-3 and
	return size;
}
