static int swevent_hlist_get(struct perf_event *event)
{
	int err;
	int cpu, failed_cpu;

	if (event->cpu != -1)
		return swevent_hlist_get_cpu(event, event->cpu);

	get_online_cpus();
	for_each_possible_cpu(cpu) {
		err = swevent_hlist_get_cpu(event, cpu);
		if (err) {
			failed_cpu = cpu;
			goto fail;
		}
	}
	put_online_cpus();

	return 0;
fail:
	for_each_possible_cpu(cpu) {
		if (cpu == failed_cpu)
			break;
		swevent_hlist_put_cpu(event, cpu);
	}

	put_online_cpus();
	return err;
}
