side_get_n_unix_fds (ProxySide *side, int n_fds)
{
  GList *res = NULL;

  while (side->control_messages != NULL)
    {
      GSocketControlMessage *control_message = side->control_messages->data;

      if (G_IS_UNIX_FD_MESSAGE (control_message))
        {
          GUnixFDMessage *fd_message = G_UNIX_FD_MESSAGE (control_message);
          GUnixFDList *fd_list = g_unix_fd_message_get_fd_list (fd_message);
          int len = g_unix_fd_list_get_length (fd_list);

          /* I believe that socket control messages are never merged, and
             the sender side sends only one unix-fd-list per message, so
             at this point there should always be one full fd list
             per requested number of fds */
          if (len != n_fds)
            {
              g_warning ("Not right nr of fds in socket message");
              return NULL;
            }

          side->control_messages = g_list_delete_link (side->control_messages, side->control_messages);

          return g_list_append (NULL, control_message);
        }

      g_object_unref (control_message);
      side->control_messages = g_list_delete_link (side->control_messages, side->control_messages);
    }

  return res;
}
