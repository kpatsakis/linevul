running_bfd(void)
{
	return (__test_bit(DAEMON_BFD, &daemon_mode) &&
	    (global_data->have_bfd_config ||
	     __test_bit(RUN_ALL_CHILDREN, &daemon_mode)));
}
