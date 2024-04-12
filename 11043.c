flatpak_proxy_set_property (GObject      *object,
                            guint         prop_id,
                            const GValue *value,
                            GParamSpec   *pspec)
{
  FlatpakProxy *proxy = FLATPAK_PROXY (object);

  switch (prop_id)
    {
    case PROP_DBUS_ADDRESS:
      proxy->dbus_address = g_value_dup_string (value);
      break;

    case PROP_SOCKET_PATH:
      proxy->socket_path = g_value_dup_string (value);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}
