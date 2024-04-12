group_sched_in(struct perf_event *group_event,
	       struct perf_cpu_context *cpuctx,
	       struct perf_event_context *ctx)
{
	struct perf_event *event, *partial_group = NULL;
	struct pmu *pmu = group_event->pmu;
	u64 now = ctx->time;
	bool simulate = false;

	if (group_event->state == PERF_EVENT_STATE_OFF)
		return 0;

	pmu->start_txn(pmu);

	if (event_sched_in(group_event, cpuctx, ctx)) {
		pmu->cancel_txn(pmu);
		return -EAGAIN;
	}

	/*
	 * Schedule in siblings as one group (if any):
	 */
	list_for_each_entry(event, &group_event->sibling_list, group_entry) {
		if (event_sched_in(event, cpuctx, ctx)) {
			partial_group = event;
			goto group_error;
		}
	}

	if (!pmu->commit_txn(pmu))
		return 0;

group_error:
	/*
	 * Groups can be scheduled in as one unit only, so undo any
	 * partial group before returning:
	 * The events up to the failed event are scheduled out normally,
	 * tstamp_stopped will be updated.
	 *
	 * The failed events and the remaining siblings need to have
	 * their timings updated as if they had gone thru event_sched_in()
	 * and event_sched_out(). This is required to get consistent timings
	 * across the group. This also takes care of the case where the group
	 * could never be scheduled by ensuring tstamp_stopped is set to mark
	 * the time the event was actually stopped, such that time delta
	 * calculation in update_event_times() is correct.
	 */
	list_for_each_entry(event, &group_event->sibling_list, group_entry) {
		if (event == partial_group)
			simulate = true;

		if (simulate) {
			event->tstamp_running += now - event->tstamp_stopped;
			event->tstamp_stopped = now;
		} else {
			event_sched_out(event, cpuctx, ctx);
		}
	}
	event_sched_out(group_event, cpuctx, ctx);

	pmu->cancel_txn(pmu);

	return -EAGAIN;
}
