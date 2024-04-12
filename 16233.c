istr_set_insert (GHashTable *table,
                 const char *istr)
{
    char *key;

    key = g_strdup (istr);
    g_hash_table_replace (table, key, key);
}
