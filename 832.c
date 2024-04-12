static int addr_compare(const struct inetpeer_addr *a,
			const struct inetpeer_addr *b)
{
	int i, n = (a->family == AF_INET ? 1 : 4);

	for (i = 0; i < n; i++) {
		if (a->addr.a6[i] == b->addr.a6[i])
			continue;
		if (a->addr.a6[i] < b->addr.a6[i])
			return -1;
		return 1;
	}

	return 0;
}
