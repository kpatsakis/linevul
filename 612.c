void RenderWidgetHostImpl::TickActiveSmoothScrollGesture() {
  TRACE_EVENT0("input", "RenderWidgetHostImpl::TickActiveSmoothScrollGesture");
  tick_active_smooth_scroll_gestures_task_posted_ = false;
  if (active_smooth_scroll_gestures_.empty()) {
    TRACE_EVENT_INSTANT0("input", "EarlyOut_NoActiveScrollGesture");
    return;
  }

  base::TimeTicks now = TimeTicks::HighResNow();
  base::TimeDelta preferred_interval =
      base::TimeDelta::FromMilliseconds(kSyntheticScrollMessageIntervalMs);
  base::TimeDelta time_until_next_ideal_interval =
      (last_smooth_scroll_gestures_tick_time_ + preferred_interval) -
      now;
  if (time_until_next_ideal_interval.InMilliseconds() > 0) {
    TRACE_EVENT_INSTANT1(
        "input", "EarlyOut_TickedTooRecently",
        "delay", time_until_next_ideal_interval.InMilliseconds());
    tick_active_smooth_scroll_gestures_task_posted_ = true;
    MessageLoop::current()->PostDelayedTask(
        FROM_HERE,
        base::Bind(&RenderWidgetHostImpl::TickActiveSmoothScrollGesture,
                   weak_factory_.GetWeakPtr()),
        time_until_next_ideal_interval);
    return;
  }

  last_smooth_scroll_gestures_tick_time_ = now;

  std::vector<int> ids_that_are_done;
  for (SmoothScrollGestureMap::iterator it =
           active_smooth_scroll_gestures_.begin();
       it != active_smooth_scroll_gestures_.end();
       ++it) {

    bool active = it->second->ForwardInputEvents(now, this);
    if (!active)
      ids_that_are_done.push_back(it->first);
  }

  for(size_t i = 0; i < ids_that_are_done.size(); i++) {
    int id = ids_that_are_done[i];
    SmoothScrollGestureMap::iterator it =
        active_smooth_scroll_gestures_.find(id);
    DCHECK(it != active_smooth_scroll_gestures_.end());
    active_smooth_scroll_gestures_.erase(it);

    Send(new ViewMsg_SmoothScrollCompleted(routing_id_, id));
  }

  if (!in_process_event_types_.empty())
    return;

  TRACE_EVENT_INSTANT1("input", "PostTickTask",
                       "delay", preferred_interval.InMilliseconds());
  tick_active_smooth_scroll_gestures_task_posted_ = true;
  MessageLoop::current()->PostDelayedTask(
      FROM_HERE,
      base::Bind(&RenderWidgetHostImpl::TickActiveSmoothScrollGesture,
                 weak_factory_.GetWeakPtr()),
      preferred_interval);
}
