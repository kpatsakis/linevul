static int start_khugepaged(void)
{
	int err = 0;
	if (khugepaged_enabled()) {
		int wakeup;
		if (unlikely(!mm_slot_cache || !mm_slots_hash)) {
			err = -ENOMEM;
			goto out;
		}
		mutex_lock(&khugepaged_mutex);
		if (!khugepaged_thread)
			khugepaged_thread = kthread_run(khugepaged, NULL,
							"khugepaged");
		if (unlikely(IS_ERR(khugepaged_thread))) {
			printk(KERN_ERR
			       "khugepaged: kthread_run(khugepaged) failed\n");
			err = PTR_ERR(khugepaged_thread);
			khugepaged_thread = NULL;
		}
		wakeup = !list_empty(&khugepaged_scan.mm_head);
		mutex_unlock(&khugepaged_mutex);
		if (wakeup)
			wake_up_interruptible(&khugepaged_wait);

		set_recommended_min_free_kbytes();
	} else
		/* wakeup to exit */
		wake_up_interruptible(&khugepaged_wait);
out:
	return err;
}
