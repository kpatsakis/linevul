compat_user_backtrace(struct compat_frame_tail __user *tail,
		      struct perf_callchain_entry *entry)
{
	struct compat_frame_tail buftail;
	unsigned long err;

	/* Also check accessibility of one struct frame_tail beyond */
	if (!access_ok(VERIFY_READ, tail, sizeof(buftail)))
		return NULL;

	pagefault_disable();
	err = __copy_from_user_inatomic(&buftail, tail, sizeof(buftail));
	pagefault_enable();

	if (err)
		return NULL;

	perf_callchain_store(entry, buftail.lr);

	/*
	 * Frame pointers should strictly progress back up the stack
	 * (towards higher addresses).
	 */
	if (tail + 1 >= (struct compat_frame_tail __user *)
			compat_ptr(buftail.fp))
		return NULL;

	return (struct compat_frame_tail __user *)compat_ptr(buftail.fp) - 1;
}
