void rpc_init_wait_queue(struct rpc_wait_queue *queue, const char *qname)
{
	__rpc_init_priority_wait_queue(queue, qname, 1);
}
