base::TimeDelta RendererSchedulerImpl::MostRecentExpectedQueueingTime() {
  return main_thread_only().most_recent_expected_queueing_time;
}
