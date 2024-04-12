flatpak_proxy_client_update_unique_id_policy (FlatpakProxyClient *client,
                                              const char         *unique_id,
                                              FlatpakPolicy       policy)
{
  if (policy > FLATPAK_POLICY_NONE)
    {
      FlatpakPolicy old_policy;
      old_policy = GPOINTER_TO_UINT (g_hash_table_lookup (client->unique_id_policy, unique_id));
      if (policy > old_policy)
        g_hash_table_replace (client->unique_id_policy, g_strdup (unique_id), GINT_TO_POINTER (policy));
    }
}
