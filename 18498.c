static int xen_memory_notifier(struct notifier_block *nb, unsigned long val, void *v)
{
	if (val == MEM_ONLINE)
		schedule_delayed_work(&balloon_worker, 0);

	return NOTIFY_OK;
}
