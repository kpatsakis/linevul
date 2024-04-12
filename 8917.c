int imap_search(struct Context *ctx, const struct Pattern *pat)
{
  struct Buffer buf;
  struct ImapData *idata = ctx->data;
  for (int i = 0; i < ctx->msgcount; i++)
    ctx->hdrs[i]->matched = false;

  if (do_search(pat, 1) == 0)
    return 0;

  mutt_buffer_init(&buf);
  mutt_buffer_addstr(&buf, "UID SEARCH ");
  if (compile_search(ctx, pat, &buf) < 0)
  {
    FREE(&buf.data);
    return -1;
  }
  if (imap_exec(idata, buf.data, 0) < 0)
  {
    FREE(&buf.data);
    return -1;
  }

  FREE(&buf.data);
  return 0;
}
