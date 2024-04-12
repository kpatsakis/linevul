static void do_pcd_read_drq(void)
{
	unsigned long saved_flags;

	if (pcd_completion(pcd_current, pcd_buffer, "read block")) {
		if (pcd_retries < PCD_RETRIES) {
			mdelay(1);
			pcd_retries++;
			pi_do_claimed(pcd_current->pi, pcd_start);
			return;
		}
		pcd_bufblk = -1;
		next_request(BLK_STS_IOERR);
		return;
	}

	do_pcd_read();
	spin_lock_irqsave(&pcd_lock, saved_flags);
	pcd_request();
	spin_unlock_irqrestore(&pcd_lock, saved_flags);
}
