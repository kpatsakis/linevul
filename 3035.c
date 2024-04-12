static bool is_orphaned_event(struct perf_event *event)
{
	return event && !is_kernel_event(event) && !event->owner;
}
