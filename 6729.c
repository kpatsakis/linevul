static inline int blk_send_start_stop(struct request_queue *q,
				      struct gendisk *bd_disk, int data)
{
	return __blk_send_generic(q, bd_disk, GPCMD_START_STOP_UNIT, data);
}
