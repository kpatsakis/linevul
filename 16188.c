void perf_event_header__init_id(struct perf_event_header *header,
				struct perf_sample_data *data,
				struct perf_event *event)
{
	if (event->attr.sample_id_all)
		__perf_event_header__init_id(header, data, event);
}
