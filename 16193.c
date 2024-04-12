fep_client_dispatch (FepClient *client)
{
  static const struct
  {
    FepControlCommand command;
    void (*handler) (FepClient *client,
		     FepControlMessage *request,
		     FepControlMessage *response);
  } handlers[] =
      {
	{ FEP_CONTROL_KEY_EVENT, command_key_event },
	{ FEP_CONTROL_RESIZE_EVENT, command_resize_event },
      };
  FepControlMessage request, response;
  int retval;
  int i;

  retval = _fep_read_control_message (client->control, &request);
  if (retval < 0)
    return -1;

  for (i = 0;
       i < SIZEOF (handlers) && handlers[i].command != request.command;
       i++)
    ;
  if (i == SIZEOF (handlers))
    {
      _fep_control_message_free_args (&request);
      fep_log (FEP_LOG_LEVEL_WARNING,
	       "no handler defined for %d", request.command);
      return -1;
    }

  client->filter_running = true;
  handlers[i].handler (client, &request, &response);
  _fep_control_message_free_args (&request);
  _fep_write_control_message (client->control, &response);
  _fep_control_message_free_args (&response);
  client->filter_running = false;

  /* flush queued messages during handler is executed */
  while (client->messages)
    {
      FepList *_head = client->messages;
      FepControlMessage *_message = _head->data;

      client->messages = _head->next;

      _fep_write_control_message (client->control, _message);
      _fep_control_message_free (_message);
      free (_head);
    }

  return retval;
}
