find_name_in_info (gconstpointer a, gconstpointer b)
{
  const DBusGProxyNameOwnerInfo *info = a;
  const char *name = b;

  return strcmp (info->name, name);
}
