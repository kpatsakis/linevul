static struct perf_callchain_entry *perf_callchain(struct pt_regs *regs)
{
	int rctx;
	struct perf_callchain_entry *entry;


	entry = get_callchain_entry(&rctx);
	if (rctx == -1)
		return NULL;

	if (!entry)
		goto exit_put;

	entry->nr = 0;

	if (!user_mode(regs)) {
		perf_callchain_store(entry, PERF_CONTEXT_KERNEL);
		perf_callchain_kernel(entry, regs);
		if (current->mm)
			regs = task_pt_regs(current);
		else
			regs = NULL;
	}

	if (regs) {
		perf_callchain_store(entry, PERF_CONTEXT_USER);
		perf_callchain_user(entry, regs);
	}

exit_put:
	put_callchain_entry(rctx);

	return entry;
}
