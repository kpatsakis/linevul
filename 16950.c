getnetnum(
	const char *num,
	sockaddr_u *addr,
	int complain,
	enum gnn_type a_type	/* ignored */
	)
{
	NTP_REQUIRE(AF_UNSPEC == AF(addr) ||
		    AF_INET == AF(addr) ||
		    AF_INET6 == AF(addr));

	if (!is_ip_address(num, AF(addr), addr))
		return 0;

	if (IS_IPV6(addr) && !ipv6_works)
		return -1;

# ifdef ISC_PLATFORM_HAVESALEN
	addr->sa.sa_len = SIZEOF_SOCKADDR(AF(addr));
# endif
	SET_PORT(addr, NTP_PORT);

	DPRINTF(2, ("getnetnum given %s, got %s\n", num, stoa(addr)));

	return 1;
}
