flatpak_proxy_init (FlatpakProxy *proxy)
{
  proxy->policy = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, NULL);
  proxy->filters = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, (GDestroyNotify)filter_list_free);
  proxy->wildcard_policy = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, NULL);
  flatpak_proxy_add_policy (proxy, "org.freedesktop.DBus", FLATPAK_POLICY_TALK);
}
