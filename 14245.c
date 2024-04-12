static int __blk_send_generic(struct request_queue *q, struct gendisk *bd_disk,
			      int cmd, int data)
{
	struct request *rq;
	int err;

	rq = blk_get_request(q, WRITE, __GFP_WAIT);
	rq->cmd_type = REQ_TYPE_BLOCK_PC;
	rq->timeout = BLK_DEFAULT_SG_TIMEOUT;
	rq->cmd[0] = cmd;
	rq->cmd[4] = data;
	rq->cmd_len = 6;
	err = blk_execute_rq(q, bd_disk, rq, 0);
	blk_put_request(rq);

	return err;
}
