static int mem_cgroup_do_precharge(unsigned long count)
{
	int ret = 0;
	int batch_count = PRECHARGE_COUNT_AT_ONCE;
	struct mem_cgroup *memcg = mc.to;

	if (mem_cgroup_is_root(memcg)) {
		mc.precharge += count;
		/* we don't need css_get for root */
		return ret;
	}
	/* try to charge at once */
	if (count > 1) {
		struct res_counter *dummy;
		/*
		 * "memcg" cannot be under rmdir() because we've already checked
		 * by cgroup_lock_live_cgroup() that it is not removed and we
		 * are still under the same cgroup_mutex. So we can postpone
		 * css_get().
		 */
		if (res_counter_charge(&memcg->res, PAGE_SIZE * count, &dummy))
			goto one_by_one;
		if (do_swap_account && res_counter_charge(&memcg->memsw,
						PAGE_SIZE * count, &dummy)) {
			res_counter_uncharge(&memcg->res, PAGE_SIZE * count);
			goto one_by_one;
		}
		mc.precharge += count;
		return ret;
	}
one_by_one:
	/* fall back to one by one charge */
	while (count--) {
		if (signal_pending(current)) {
			ret = -EINTR;
			break;
		}
		if (!batch_count--) {
			batch_count = PRECHARGE_COUNT_AT_ONCE;
			cond_resched();
		}
		ret = __mem_cgroup_try_charge(NULL,
					GFP_KERNEL, 1, &memcg, false);
		if (ret)
			/* mem_cgroup_clear_mc() will do uncharge later */
			return ret;
		mc.precharge++;
	}
	return ret;
}
