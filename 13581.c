void add_reflogs_to_pending(struct rev_info *revs, unsigned flags)
{
	struct all_refs_cb cb;

	cb.all_revs = revs;
	cb.all_flags = flags;
	for_each_reflog(handle_one_reflog, &cb);
}
