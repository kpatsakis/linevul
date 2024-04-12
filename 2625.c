int alloc_rt_sched_group(struct task_group *tg, struct task_group *parent)
{
	struct rt_rq *rt_rq;
	struct sched_rt_entity *rt_se;
	int i;

	tg->rt_rq = kzalloc(sizeof(rt_rq) * nr_cpu_ids, GFP_KERNEL);
	if (!tg->rt_rq)
		goto err;
	tg->rt_se = kzalloc(sizeof(rt_se) * nr_cpu_ids, GFP_KERNEL);
	if (!tg->rt_se)
		goto err;

	init_rt_bandwidth(&tg->rt_bandwidth,
			ktime_to_ns(def_rt_bandwidth.rt_period), 0);

	for_each_possible_cpu(i) {
		rt_rq = kzalloc_node(sizeof(struct rt_rq),
				     GFP_KERNEL, cpu_to_node(i));
		if (!rt_rq)
			goto err;

		rt_se = kzalloc_node(sizeof(struct sched_rt_entity),
				     GFP_KERNEL, cpu_to_node(i));
		if (!rt_se)
			goto err_free_rq;

		init_tg_rt_entry(tg, rt_rq, rt_se, i, parent->rt_se[i]);
	}

	return 1;

err_free_rq:
	kfree(rt_rq);
err:
	return 0;
}
