bus_activation_reload (BusActivation     *activation,
                       const DBusString  *address,
                       DBusList         **directories,
                       DBusError         *error)
{
  DBusList      *link;
  char          *dir;

  if (activation->server_address != NULL)
    dbus_free (activation->server_address);
  if (!_dbus_string_copy_data (address, &activation->server_address))
    {
      BUS_SET_OOM (error);
      goto failed;
    }

  if (activation->entries != NULL)
    _dbus_hash_table_unref (activation->entries);
  activation->entries = _dbus_hash_table_new (DBUS_HASH_STRING, NULL,
                                             (DBusFreeFunction)bus_activation_entry_unref);
  if (activation->entries == NULL)
    {
      BUS_SET_OOM (error);
      goto failed;
    }

  if (activation->directories != NULL)
    _dbus_hash_table_unref (activation->directories);
  activation->directories = _dbus_hash_table_new (DBUS_HASH_STRING, NULL,
                                                  (DBusFreeFunction)bus_service_directory_unref);

  if (activation->directories == NULL)
    {
      BUS_SET_OOM (error);
      goto failed;
    }

  link = _dbus_list_get_first_link (directories);
  while (link != NULL)
    {
      BusServiceDirectory *s_dir;

      dir = _dbus_strdup ((const char *) link->data);
      if (!dir)
        {
          BUS_SET_OOM (error);
          goto failed;
        }

      s_dir = dbus_new0 (BusServiceDirectory, 1);
      if (!s_dir)
        {
          dbus_free (dir);
          BUS_SET_OOM (error);
          goto failed;
        }

      s_dir->refcount = 1;
      s_dir->dir_c = dir;

      s_dir->entries = _dbus_hash_table_new (DBUS_HASH_STRING, NULL,
                                             (DBusFreeFunction)bus_activation_entry_unref);

      if (!s_dir->entries)
        {
          bus_service_directory_unref (s_dir);
          BUS_SET_OOM (error);
          goto failed;
        }

      if (!_dbus_hash_table_insert_string (activation->directories, s_dir->dir_c, s_dir))
        {
          bus_service_directory_unref (s_dir);
          BUS_SET_OOM (error);
          goto failed;
        }

      /* only fail on OOM, it is ok if we can't read the directory */
      if (!update_directory (activation, s_dir, error))
        {
          if (dbus_error_has_name (error, DBUS_ERROR_NO_MEMORY))
            goto failed;
          else
            dbus_error_free (error);
        }

      link = _dbus_list_get_next_link (directories, link);
    }

  return TRUE;
 failed:
  return FALSE;
}
