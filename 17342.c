char *imap_set_flags(struct ImapData *idata, struct Header *h, char *s, int *server_changes)
{
  struct Context *ctx = idata->ctx;
  struct ImapHeader newh = { 0 };
  struct ImapHeaderData old_hd;
  bool readonly;
  int local_changes;

  local_changes = h->changed;

  struct ImapHeaderData *hd = h->data;
  newh.data = hd;

  memcpy(&old_hd, hd, sizeof(old_hd));

  mutt_debug(2, "parsing FLAGS\n");
  s = msg_parse_flags(&newh, s);
  if (!s)
    return NULL;

  /* Update tags system */
  driver_tags_replace(&h->tags, mutt_str_strdup(hd->flags_remote));

  /* YAUH (yet another ugly hack): temporarily set context to
   * read-write even if it's read-only, so *server* updates of
   * flags can be processed by mutt_set_flag. ctx->changed must
   * be restored afterwards */
  readonly = ctx->readonly;
  ctx->readonly = false;

  /* This is redundant with the following two checks. Removing:
   * mutt_set_flag (ctx, h, MUTT_NEW, !(hd->read || hd->old));
   */
  set_changed_flag(ctx, h, local_changes, server_changes, MUTT_OLD, old_hd.old,
                   hd->old, h->old);
  set_changed_flag(ctx, h, local_changes, server_changes, MUTT_READ,
                   old_hd.read, hd->read, h->read);
  set_changed_flag(ctx, h, local_changes, server_changes, MUTT_DELETE,
                   old_hd.deleted, hd->deleted, h->deleted);
  set_changed_flag(ctx, h, local_changes, server_changes, MUTT_FLAG,
                   old_hd.flagged, hd->flagged, h->flagged);
  set_changed_flag(ctx, h, local_changes, server_changes, MUTT_REPLIED,
                   old_hd.replied, hd->replied, h->replied);

  /* this message is now definitively *not* changed (mutt_set_flag
   * marks things changed as a side-effect) */
  if (!local_changes)
    h->changed = false;
  ctx->changed &= !readonly;
  ctx->readonly = readonly;

  return s;
}
