jas_mb_t *jas_get_mb(void *ptr)
{
	return JAS_CAST(jas_mb_t *, JAS_CAST(max_align_t *, ptr) - JAS_MB_ADJUST);
}
