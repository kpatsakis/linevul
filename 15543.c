static blk_status_t pcd_queue_rq(struct blk_mq_hw_ctx *hctx,
				 const struct blk_mq_queue_data *bd)
{
	struct pcd_unit *cd = hctx->queue->queuedata;

	if (rq_data_dir(bd->rq) != READ) {
		blk_mq_start_request(bd->rq);
		return BLK_STS_IOERR;
	}

	spin_lock_irq(&pcd_lock);
	list_add_tail(&bd->rq->queuelist, &cd->rq_list);
	pcd_request();
	spin_unlock_irq(&pcd_lock);

	return BLK_STS_OK;
}
