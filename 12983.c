static void swevent_hlist_put(struct perf_event *event)
{
	int cpu;

	for_each_possible_cpu(cpu)
		swevent_hlist_put_cpu(event, cpu);
}
