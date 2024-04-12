static int cpu_clock_sample(const clockid_t which_clock,
			    struct task_struct *p, u64 *sample)
{
	switch (CPUCLOCK_WHICH(which_clock)) {
	default:
		return -EINVAL;
	case CPUCLOCK_PROF:
		*sample = prof_ticks(p);
		break;
	case CPUCLOCK_VIRT:
		*sample = virt_ticks(p);
		break;
	case CPUCLOCK_SCHED:
		*sample = task_sched_runtime(p);
		break;
	}
	return 0;
}
