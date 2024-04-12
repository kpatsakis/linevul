static void perf_swevent_cancel_hrtimer(struct perf_event *event)
{
	struct hw_perf_event *hwc = &event->hw;

	if (is_sampling_event(event)) {
		ktime_t remaining = hrtimer_get_remaining(&hwc->hrtimer);
		local64_set(&hwc->period_left, ktime_to_ns(remaining));

		hrtimer_cancel(&hwc->hrtimer);
	}
}
