static void cpu_load_update(struct rq *this_rq, unsigned long this_load,
			    unsigned long pending_updates)
{
	unsigned long __maybe_unused tickless_load = this_rq->cpu_load[0];
	int i, scale;

	this_rq->nr_load_updates++;

	/* Update our load: */
	this_rq->cpu_load[0] = this_load; /* Fasttrack for idx 0 */
	for (i = 1, scale = 2; i < CPU_LOAD_IDX_MAX; i++, scale += scale) {
		unsigned long old_load, new_load;

		/* scale is effectively 1 << i now, and >> i divides by scale */

		old_load = this_rq->cpu_load[i];
#ifdef CONFIG_NO_HZ_COMMON
		old_load = decay_load_missed(old_load, pending_updates - 1, i);
		if (tickless_load) {
			old_load -= decay_load_missed(tickless_load, pending_updates - 1, i);
			/*
			 * old_load can never be a negative value because a
			 * decayed tickless_load cannot be greater than the
			 * original tickless_load.
			 */
			old_load += tickless_load;
		}
#endif
		new_load = this_load;
		/*
		 * Round up the averaging division if load is increasing. This
		 * prevents us from getting stuck on 9 if the load is 10, for
		 * example.
		 */
		if (new_load > old_load)
			new_load += scale - 1;

		this_rq->cpu_load[i] = (old_load * (scale - 1) + new_load) >> i;
	}
}
