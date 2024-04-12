static void sched_rt_avg_update(struct rq *rq, u64 rt_delta)
{
	rq->rt_avg += rt_delta;
	sched_avg_update(rq);
}
