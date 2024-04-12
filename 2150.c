get_ping_buffer_for_header (Header *header)
{
  Buffer *buffer;
  GDBusMessage *dummy;

  dummy = g_dbus_message_new_method_call (NULL, "/", "org.freedesktop.DBus.Peer", "Ping");
  g_dbus_message_set_serial (dummy, header->serial);
  g_dbus_message_set_flags (dummy, header->flags);

  buffer = message_to_buffer (dummy);

  g_object_unref (dummy);

  return buffer;
}
