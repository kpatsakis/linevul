static struct ImapCommand *cmd_new(struct ImapData *idata)
{
  struct ImapCommand *cmd = NULL;

  if (cmd_queue_full(idata))
  {
    mutt_debug(3, "IMAP command queue full\n");
    return NULL;
  }

  cmd = idata->cmds + idata->nextcmd;
  idata->nextcmd = (idata->nextcmd + 1) % idata->cmdslots;

  snprintf(cmd->seq, sizeof(cmd->seq), "a%04u", idata->seqno++);
  if (idata->seqno > 9999)
    idata->seqno = 0;

  cmd->state = IMAP_CMD_NEW;

  return cmd;
}
