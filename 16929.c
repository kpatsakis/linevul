static struct dyn_lease *find_lease_by_nip(uint32_t nip)
{
	unsigned i;

	for (i = 0; i < server_config.max_leases; i++)
		if (g_leases[i].lease_nip == nip)
			return &g_leases[i];

	return NULL;
}
