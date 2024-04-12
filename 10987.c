lvs_flush_handler(__attribute__((unused)) vector_t *strvec)
{
	global_data->lvs_flush = true;
}
