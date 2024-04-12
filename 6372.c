simple_method_return (void)
{
  DBusMessage *message;
  message =  dbus_message_new (DBUS_MESSAGE_TYPE_METHOD_RETURN);
  if (message == NULL)
    _dbus_assert_not_reached ("oom");

  set_reply_serial (message);
  
  return message;
}
