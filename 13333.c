void seq_copy_to_input(unsigned char *event_rec, int len)
{
	unsigned long flags;

	/*
	 * Verify that the len is valid for the current mode.
	 */

	if (len != 4 && len != 8)
		return;
	if ((seq_mode == SEQ_1) != (len == 4))
		return;

	if (iqlen >= (SEQ_MAX_QUEUE - 1))
		return;		/* Overflow */

	spin_lock_irqsave(&lock,flags);
	memcpy(&iqueue[iqtail * IEV_SZ], event_rec, len);
	iqlen++;
	iqtail = (iqtail + 1) % SEQ_MAX_QUEUE;
	wake_up(&midi_sleeper);
	spin_unlock_irqrestore(&lock,flags);
}
