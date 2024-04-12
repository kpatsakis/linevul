static int rt_garbage_collect(struct dst_ops *ops)
{
	static unsigned long expire = RT_GC_TIMEOUT;
	static unsigned long last_gc;
	static int rover;
	static int equilibrium;
	struct rtable *rth;
	struct rtable __rcu **rthp;
	unsigned long now = jiffies;
	int goal;
	int entries = dst_entries_get_fast(&ipv4_dst_ops);

	/*
	 * Garbage collection is pretty expensive,
	 * do not make it too frequently.
	 */

	RT_CACHE_STAT_INC(gc_total);

	if (now - last_gc < ip_rt_gc_min_interval &&
	    entries < ip_rt_max_size) {
		RT_CACHE_STAT_INC(gc_ignored);
		goto out;
	}

	entries = dst_entries_get_slow(&ipv4_dst_ops);
	/* Calculate number of entries, which we want to expire now. */
	goal = entries - (ip_rt_gc_elasticity << rt_hash_log);
	if (goal <= 0) {
		if (equilibrium < ipv4_dst_ops.gc_thresh)
			equilibrium = ipv4_dst_ops.gc_thresh;
		goal = entries - equilibrium;
		if (goal > 0) {
			equilibrium += min_t(unsigned int, goal >> 1, rt_hash_mask + 1);
			goal = entries - equilibrium;
		}
	} else {
		/* We are in dangerous area. Try to reduce cache really
		 * aggressively.
		 */
		goal = max_t(unsigned int, goal >> 1, rt_hash_mask + 1);
		equilibrium = entries - goal;
	}

	if (now - last_gc >= ip_rt_gc_min_interval)
		last_gc = now;

	if (goal <= 0) {
		equilibrium += goal;
		goto work_done;
	}

	do {
		int i, k;

		for (i = rt_hash_mask, k = rover; i >= 0; i--) {
			unsigned long tmo = expire;

			k = (k + 1) & rt_hash_mask;
			rthp = &rt_hash_table[k].chain;
			spin_lock_bh(rt_hash_lock_addr(k));
			while ((rth = rcu_dereference_protected(*rthp,
					lockdep_is_held(rt_hash_lock_addr(k)))) != NULL) {
				if (!rt_is_expired(rth) &&
					!rt_may_expire(rth, tmo, expire)) {
					tmo >>= 1;
					rthp = &rth->dst.rt_next;
					continue;
				}
				*rthp = rth->dst.rt_next;
				rt_free(rth);
				goal--;
			}
			spin_unlock_bh(rt_hash_lock_addr(k));
			if (goal <= 0)
				break;
		}
		rover = k;

		if (goal <= 0)
			goto work_done;

		/* Goal is not achieved. We stop process if:

		   - if expire reduced to zero. Otherwise, expire is halfed.
		   - if table is not full.
		   - if we are called from interrupt.
		   - jiffies check is just fallback/debug loop breaker.
		     We will not spin here for long time in any case.
		 */

		RT_CACHE_STAT_INC(gc_goal_miss);

		if (expire == 0)
			break;

		expire >>= 1;

		if (dst_entries_get_fast(&ipv4_dst_ops) < ip_rt_max_size)
			goto out;
	} while (!in_softirq() && time_before_eq(jiffies, now));

	if (dst_entries_get_fast(&ipv4_dst_ops) < ip_rt_max_size)
		goto out;
	if (dst_entries_get_slow(&ipv4_dst_ops) < ip_rt_max_size)
		goto out;
	if (net_ratelimit())
		printk(KERN_WARNING "dst cache overflow\n");
	RT_CACHE_STAT_INC(gc_dst_overflow);
	return 1;

work_done:
	expire += ip_rt_gc_min_interval;
	if (expire > ip_rt_gc_timeout ||
	    dst_entries_get_fast(&ipv4_dst_ops) < ipv4_dst_ops.gc_thresh ||
	    dst_entries_get_slow(&ipv4_dst_ops) < ipv4_dst_ops.gc_thresh)
		expire = ip_rt_gc_timeout;
out:	return 0;
}
