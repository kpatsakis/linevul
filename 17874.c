static void update_rq_clock_task(struct rq *rq, s64 delta)
{
	rq->clock_task += delta;
}
