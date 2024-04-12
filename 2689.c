int net_ratelimit(void)
{
	return __ratelimit(&net_ratelimit_state);
}
