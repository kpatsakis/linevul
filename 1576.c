int imap_delete_mailbox(struct Context *ctx, struct ImapMbox *mx)
{
  char buf[PATH_MAX], mbox[PATH_MAX];
  struct ImapData *idata = NULL;

  if (!ctx || !ctx->data)
  {
    idata = imap_conn_find(&mx->account, ImapPassive ? MUTT_IMAP_CONN_NONEW : 0);
    if (!idata)
    {
      FREE(&mx->mbox);
      return -1;
    }
  }
  else
  {
    idata = ctx->data;
  }

  imap_munge_mbox_name(idata, mbox, sizeof(mbox), mx->mbox);
  snprintf(buf, sizeof(buf), "DELETE %s", mbox);

  if (imap_exec(idata, buf, 0) != 0)
    return -1;

  return 0;
}
