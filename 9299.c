void *set_vi_handler(int n, vi_handler_t addr)
{
	return set_vi_srs_handler(n, addr, 0);
}
