static void cpu_clock_event_read(struct perf_event *event)
{
	cpu_clock_event_update(event);
}
