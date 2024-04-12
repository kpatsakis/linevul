void *tracing_cond_snapshot_data(struct trace_array *tr)
{
	void *cond_data = NULL;

	arch_spin_lock(&tr->max_lock);

	if (tr->cond_snapshot)
		cond_data = tr->cond_snapshot->cond_data;

	arch_spin_unlock(&tr->max_lock);

	return cond_data;
}
