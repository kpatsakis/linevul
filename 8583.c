vrrp_evip_handler(vector_t *strvec)
{
	alloc_value_block(alloc_vrrp_evip, vector_slot(strvec, 0));
}
