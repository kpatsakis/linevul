static int get_free_idx(void)
{
	struct thread_struct *t = &current->thread;
	int idx;

	for (idx = 0; idx < GDT_ENTRY_TLS_ENTRIES; idx++)
		if (desc_empty(&t->tls_array[idx]))
			return idx + GDT_ENTRY_TLS_MIN;
 	return -ESRCH;
 }
