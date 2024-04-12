magic_close(struct magic_set *ms)
{
	if (ms == NULL)
		return;
	file_ms_free(ms);
}
