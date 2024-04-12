int id_lookup_value(void *ptr)
{
  return g_hash_table_find(g_ids, id_match_value, &ptr) ? (uintptr_t)ptr : -1;
}
