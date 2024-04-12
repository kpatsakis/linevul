static int perf_event_mmap_match(struct perf_event *event,
				   struct perf_mmap_event *mmap_event,
				   int executable)
{
	if (event->state < PERF_EVENT_STATE_INACTIVE)
		return 0;

	if (!event_filter_match(event))
		return 0;

	if ((!executable && event->attr.mmap_data) ||
	    (executable && event->attr.mmap))
		return 1;

	return 0;
}
