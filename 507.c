int hostap_tx_callback_unregister(local_info_t *local, u16 idx)
{
	unsigned long flags;
	struct hostap_tx_callback_info *cb, *prev = NULL;

	spin_lock_irqsave(&local->lock, flags);
	cb = local->tx_callback;
	while (cb != NULL && cb->idx != idx) {
		prev = cb;
		cb = cb->next;
	}
	if (cb) {
		if (prev == NULL)
			local->tx_callback = cb->next;
		else
			prev->next = cb->next;
		kfree(cb);
	}
	spin_unlock_irqrestore(&local->lock, flags);

	return cb ? 0 : -1;
}
