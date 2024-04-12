static int ksm_memory_callback(struct notifier_block *self,
			       unsigned long action, void *arg)
{
	struct memory_notify *mn = arg;
	struct stable_node *stable_node;

	switch (action) {
	case MEM_GOING_OFFLINE:
		/*
		 * Keep it very simple for now: just lock out ksmd and
		 * MADV_UNMERGEABLE while any memory is going offline.
		 * mutex_lock_nested() is necessary because lockdep was alarmed
		 * that here we take ksm_thread_mutex inside notifier chain
		 * mutex, and later take notifier chain mutex inside
		 * ksm_thread_mutex to unlock it.   But that's safe because both
		 * are inside mem_hotplug_mutex.
		 */
		mutex_lock_nested(&ksm_thread_mutex, SINGLE_DEPTH_NESTING);
		break;

	case MEM_OFFLINE:
		/*
		 * Most of the work is done by page migration; but there might
		 * be a few stable_nodes left over, still pointing to struct
		 * pages which have been offlined: prune those from the tree.
		 */
		while ((stable_node = ksm_check_stable_tree(mn->start_pfn,
					mn->start_pfn + mn->nr_pages)) != NULL)
			remove_node_from_stable_tree(stable_node);
		/* fallthrough */

	case MEM_CANCEL_OFFLINE:
		mutex_unlock(&ksm_thread_mutex);
		break;
	}
	return NOTIFY_OK;
}
