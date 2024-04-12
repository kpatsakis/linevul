static int do_wait_thread(struct wait_opts *wo, struct task_struct *tsk)
{
	struct task_struct *p;

	list_for_each_entry(p, &tsk->children, sibling) {
		int ret = wait_consider_task(wo, 0, p);

		if (ret)
			return ret;
	}

	return 0;
}
