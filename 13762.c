int imap_buffy_check(int check_stats)
{
  struct ImapData *idata = NULL;
  struct ImapData *lastdata = NULL;
  struct Buffy *mailbox = NULL;
  char name[LONG_STRING];
  char command[LONG_STRING];
  char munged[LONG_STRING];
  int buffies = 0;

  for (mailbox = Incoming; mailbox; mailbox = mailbox->next)
  {
    /* Init newly-added mailboxes */
    if (!mailbox->magic)
    {
      if (mx_is_imap(mailbox->path))
        mailbox->magic = MUTT_IMAP;
    }

    if (mailbox->magic != MUTT_IMAP)
      continue;

    if (get_mailbox(mailbox->path, &idata, name, sizeof(name)) < 0)
    {
      mailbox->new = false;
      continue;
    }

    /* Don't issue STATUS on the selected mailbox, it will be NOOPed or
     * IDLEd elsewhere.
     * idata->mailbox may be NULL for connections other than the current
     * mailbox's, and shouldn't expand to INBOX in that case. #3216. */
    if (idata->mailbox && (imap_mxcmp(name, idata->mailbox) == 0))
    {
      mailbox->new = false;
      continue;
    }

    if (!mutt_bit_isset(idata->capabilities, IMAP4REV1) &&
        !mutt_bit_isset(idata->capabilities, STATUS))
    {
      mutt_debug(2, "Server doesn't support STATUS\n");
      continue;
    }

    if (lastdata && idata != lastdata)
    {
      /* Send commands to previous server. Sorting the buffy list
       * may prevent some infelicitous interleavings */
      if (imap_exec(lastdata, NULL, IMAP_CMD_FAIL_OK | IMAP_CMD_POLL) == -1)
        mutt_debug(1, "#1 Error polling mailboxes\n");

      lastdata = NULL;
    }

    if (!lastdata)
      lastdata = idata;

    imap_munge_mbox_name(idata, munged, sizeof(munged), name);
    if (check_stats)
    {
      snprintf(command, sizeof(command),
               "STATUS %s (UIDNEXT UIDVALIDITY UNSEEN RECENT MESSAGES)", munged);
    }
    else
    {
      snprintf(command, sizeof(command),
               "STATUS %s (UIDNEXT UIDVALIDITY UNSEEN RECENT)", munged);
    }

    if (imap_exec(idata, command, IMAP_CMD_QUEUE | IMAP_CMD_POLL) < 0)
    {
      mutt_debug(1, "Error queueing command\n");
      return 0;
    }
  }

  if (lastdata && (imap_exec(lastdata, NULL, IMAP_CMD_FAIL_OK | IMAP_CMD_POLL) == -1))
  {
    mutt_debug(1, "#2 Error polling mailboxes\n");
    return 0;
  }

  /* collect results */
  for (mailbox = Incoming; mailbox; mailbox = mailbox->next)
  {
    if (mailbox->magic == MUTT_IMAP && mailbox->new)
      buffies++;
  }

  return buffies;
}
