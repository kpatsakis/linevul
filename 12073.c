static void update_group_shares_cpu(struct task_group *tg, int cpu,
				    unsigned long sd_shares,
				    unsigned long sd_rq_weight,
				    unsigned long *usd_rq_weight)
{
	unsigned long shares, rq_weight;
	int boost = 0;

	rq_weight = usd_rq_weight[cpu];
	if (!rq_weight) {
		boost = 1;
		rq_weight = NICE_0_LOAD;
	}

	/*
	 *             \Sum_j shares_j * rq_weight_i
	 * shares_i =  -----------------------------
	 *                  \Sum_j rq_weight_j
	 */
	shares = (sd_shares * rq_weight) / sd_rq_weight;
	shares = clamp_t(unsigned long, shares, MIN_SHARES, MAX_SHARES);

	if (abs(shares - tg->se[cpu]->load.weight) >
			sysctl_sched_shares_thresh) {
		struct rq *rq = cpu_rq(cpu);
		unsigned long flags;

		raw_spin_lock_irqsave(&rq->lock, flags);
		tg->cfs_rq[cpu]->rq_weight = boost ? 0 : rq_weight;
		tg->cfs_rq[cpu]->shares = boost ? 0 : shares;
		__set_se_shares(tg->se[cpu], shares);
		raw_spin_unlock_irqrestore(&rq->lock, flags);
	}
}
