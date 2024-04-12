int perf_register_guest_info_callbacks(struct perf_guest_info_callbacks *cbs)
{
	perf_guest_cbs = cbs;
	return 0;
}
