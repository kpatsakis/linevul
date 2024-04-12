static void kiocb_batch_init(struct kiocb_batch *batch, long total)
{
	INIT_LIST_HEAD(&batch->head);
 	batch->count = total;
 }
