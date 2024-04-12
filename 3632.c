static void mipspmu_start(struct perf_event *event, int flags)
{
	struct hw_perf_event *hwc = &event->hw;

	if (!mipspmu)
		return;

	if (flags & PERF_EF_RELOAD)
		WARN_ON_ONCE(!(hwc->state & PERF_HES_UPTODATE));

	hwc->state = 0;

	/* Set the period for the event. */
	mipspmu_event_set_period(event, hwc, hwc->idx);

	/* Enable the event. */
	mipspmu->enable_event(hwc, hwc->idx);
}
