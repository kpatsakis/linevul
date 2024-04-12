static enum iwch_ep_state state_read(struct iwch_ep_common *epc)
{
	unsigned long flags;
	enum iwch_ep_state state;

	spin_lock_irqsave(&epc->lock, flags);
	state = epc->state;
	spin_unlock_irqrestore(&epc->lock, flags);
	return state;
}
