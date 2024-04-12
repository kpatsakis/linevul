static inline void npidentifier_cache_create(void)
{
  g_npidentifier_cache =
	g_hash_table_new_full(NULL, NULL, NULL,
						  (GDestroyNotify)npidentifier_info_destroy);
}
