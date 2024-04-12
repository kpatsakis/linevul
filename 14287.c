void id_link(int id, void *ptr)
{
  g_hash_table_insert(g_ids, id_key(id), ptr);
}
