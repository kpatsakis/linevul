static int uwbd(void *param)
{
	struct uwb_rc *rc = param;
	unsigned long flags;
	struct uwb_event *evt;
	int should_stop = 0;

	while (1) {
		wait_event_interruptible_timeout(
			rc->uwbd.wq,
			!list_empty(&rc->uwbd.event_list)
			  || (should_stop = kthread_should_stop()),
			HZ);
		if (should_stop)
			break;

		spin_lock_irqsave(&rc->uwbd.event_list_lock, flags);
		if (!list_empty(&rc->uwbd.event_list)) {
			evt = list_first_entry(&rc->uwbd.event_list, struct uwb_event, list_node);
			list_del(&evt->list_node);
		} else
			evt = NULL;
		spin_unlock_irqrestore(&rc->uwbd.event_list_lock, flags);

		if (evt) {
			uwbd_event_handle(evt);
			kfree(evt);
		}

		uwb_beca_purge(rc);	/* Purge devices that left */
	}
	return 0;
}
