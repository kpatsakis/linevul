void MediaRecorder::ScheduleDispatchEvent(Event* event) {
  scheduled_events_.push_back(event);

  dispatch_scheduled_event_runner_->RunAsync();
}
