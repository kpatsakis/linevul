static void rpc_final_put_task(struct rpc_task *task,
		struct workqueue_struct *q)
{
	if (q != NULL) {
		INIT_WORK(&task->u.tk_work, rpc_async_release);
		queue_work(q, &task->u.tk_work);
	} else
		rpc_free_task(task);
}
