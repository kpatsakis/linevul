static inline void next_request(blk_status_t err)
{
	unsigned long saved_flags;

	spin_lock_irqsave(&pcd_lock, saved_flags);
	if (!blk_update_request(pcd_req, err, blk_rq_cur_bytes(pcd_req))) {
		__blk_mq_end_request(pcd_req, err);
		pcd_req = NULL;
	}
	pcd_busy = 0;
	pcd_request();
	spin_unlock_irqrestore(&pcd_lock, saved_flags);
}
