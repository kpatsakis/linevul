void perf_log_lost_samples(struct perf_event *event, u64 lost)
{
	struct perf_output_handle handle;
	struct perf_sample_data sample;
	int ret;

	struct {
		struct perf_event_header	header;
		u64				lost;
	} lost_samples_event = {
		.header = {
			.type = PERF_RECORD_LOST_SAMPLES,
			.misc = 0,
			.size = sizeof(lost_samples_event),
		},
		.lost		= lost,
	};

	perf_event_header__init_id(&lost_samples_event.header, &sample, event);

	ret = perf_output_begin(&handle, event,
				lost_samples_event.header.size);
	if (ret)
		return;

	perf_output_put(&handle, lost_samples_event);
	perf_event__output_id_sample(event, &handle, &sample);
	perf_output_end(&handle);
}
